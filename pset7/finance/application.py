from cs50 import SQL #importa sql y funciones de ayuda
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    pf = db.execute("select symbol, shares from portfolio where user_id = :id", id=session["user_id"])

    stonks = 0

    for p in pf:
        symbol = p["symbol"]
        shares = p["shares"]
        price = lookup(symbol)
        total = price * shares
        stonks += total
        db.execute("update portfolio set price = :pr, total = :t where symbol = :sym and user_id = :id",
                pr=price, t=total, sym=symbol, id=session["user_id"])

    u = db.execute("select cash from users where id=:id", id=session["user_id"])

    cash = u[0]["cash"]

    stonks += cash

    npf = db.execute("select * from portfolio where user_id = :id", id=session["user_id"])

    transactions = db.execute(
        "SELECT symbol,SUM(share) as shares, price_per_share as price,SUM(TOTAL) as total  FROM transactions WHERE user_id = :id GROUP BY symbol, price_per_share", id=session["user_id"])

    return render_template("index.html", cash=usd(cash), stonks=usd(stonks), transactions=transactions)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # si el simbolo existe
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("Simbolo invalido", 400)

        # si share tiene un entero positivo
        try:
            share = int(request.form.get("shares"))
        except:
            return apology("Las acciones deben ser positivas", 400)

        # si las acciones solicitadas son 0
        if share <= 0:
            return apology("Debes solicitar un numero de acciones")

        # consulta la base de datos para el username
        rows = db.execute("SELECT cash FROM users  WHERE id = :user_id", user_id=session["user_id"])

        # dinero que el usuario dispone en la cuenta
        cash_remaining = rows[0]["cash"]
        price_per_share = quote["price"]

        # calcula el precio de las acciones solicitadas
        total_price = price_per_share * share

        if total_price > cash_remaining:
            return apology("No posee fondos suficientes para completar esta accion")

        # TODO = transaccion
        db.execute("UPDATE users SET cash = cash- :price WHERE id = :user_id", price=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO  transactions (user_id, symbol, share, price_per_share, TOTAL) VALUES (:user_id, :symbol, :share, :price, :total)",
                    user_id=session["user_id"],
                symbol=request.form.get("symbol"),
                share=share,
                price=price_per_share, total=total_price)
        flash("Comprado!")

        return redirect(url_for("index"))
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, share, price_per_share, date FROM transactions WHERE user_id = :user_id ORDER BY date",
                            user_id=session["user_id"])

    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """ allow user to change her password """

    if request.method == "POST":

        # verifica si la contraseña actual no esta vacia
        if not request.form.get("current_password"):
            return apology("Debe ingresar su contraseña actual", 400)

        # consulta la base de datos para el user_id
        rows = db.execute("SELECT hash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # verifica si la contraseña actual es correcta
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("current_password")):
            return apology("Contraseña invalida", 400)

        # verifica si la nueva contraseña no esta vacia
        if not request.form.get("new_password"):
            return apology("Debe ingresar una nueva contraseña", 400)

        # verifica si la confirmacion de la nueva contraseña no esta vacia
        elif not request.form.get("new_password_confirmation"):
            return apology("Debe confirmar su nueva contraseña", 400)

        # verifica que la nueva contraseña y la confirmacion coincidan
        elif request.form.get("new_password") != request.form.get("new_password_confirmation"):
            return apology("Su nueva contraseña y la confirmacion deben coincidir", 400)

        # actualiza la base de datos
        hash = generate_password_hash(request.form.get("new_password"))
        rows = db.execute("UPDATE users SET hash = :hash WHERE id = :user_id", user_id=session["user_id"], hash=hash)

        # muestra el cambio
        flash("Se ha cambiado la contraseña")

    return render_template("change_password.html")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("insert symbol")

        q = lookup(request.form.get("symbol"))

        if not q:
            return apology("simbolo invalido")
        else:
            return render_template("quoted.html", symbol=q["symbol"], price=q["price"])
    else:
        return render_template("quote.html")

    # else request.method == "GET":
        # return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("El usuario esta vacio")
        if not password:
            return apology("No hay una contraseña")
        if not confirmation:
            return apology("Se necesita confirmar la contraseña")
        if password != confirmation:
            return apology("La contraseña debe coincidir")

        if db.execute("SELECT username FROM users WHERE username = :username", username=request.form["username"]):
            return apology("El nombre de usuario ya existe, intenta con otro")

        id = db.execute("INSERT INTO users(username, hash) VALUES (:username,:pwd)",
                        username=request.form["username"], pwd=generate_password_hash(request.form["password"]))

        session["user_id"] = id

        return redirect("/")

    elif request.method == "GET":
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Acciones invalidas", 400)
        quote = lookup(request.form.get("symbol"))
        # checa si el simbolo existe
        if quote == None:
            return apology("Simbolo invalido", 400)

        # checa si las acciones tienen numeros positivos
        if not request.form.get("shares").isnumeric() or int(request.form.get("shares")) < 1:
            return apology("Accion incorrecta", 400)
        try:
            share = int(request.form.get("shares"))
        except:
            return apology("Las acciones deben ser positivas", 400)

        # si las acciones solicitadas son 0
        if share <= 0:
            return apology("Debes solicitar un numero de acciones", 400)
        # consulta la base de datos para el username
        rows = db.execute("SELECT cash FROM users  WHERE id = :user_id", user_id=session["user_id"])
        # dinero que el usuario dispone en la cuenta
        cash_remaining = rows[0]["cash"]
        price_per_share = quote["price"]
        # calcula el precio de las acciones solicitadas
        total_price = price_per_share * share
        if total_price > cash_remaining:
            return apology("No posee fondos suficientes para completar esta accion", 400)
        # TODO = transaccion
        db.execute("UPDATE users SET cash = cash + :price_per_share WHERE id = :user_id",
                    price_per_share=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO  transactions (user_id, symbol, share, price_per_share, TOTAL) VALUES (:user_id, :symbol, :share, :price, :TOTAL)",
                    user_id=session["user_id"],
                    symbol=request.form.get("symbol"),
                    share=share*-1,
                    price=price_per_share,
                    TOTAL=price_per_share*share*-1)
        flash("Vendido!")

        return redirect("/")

    else:
        stocks = db.execute("SELECT symbol, SUM(share) as total_share FROM transactions WHERE user_id= :user_id GROUP BY symbol HAVING total_share > 0",
                            user_id=session["user_id"])
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
