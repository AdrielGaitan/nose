from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
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
    user_id = session["user_id"]
    stocks = db.execute("SELECT symbol, name, price, SUM(shares) as totalshares\
                        FROM transactiones WHERE user_id = ? GROUP BY symbol ", user_id)

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    total = cash
    for stock in stocks:
        total += stock["price"] * stock["totalshares"]

    return render_template("index.html", stocks=stocks, cash=cash, usd=usd, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        print("Entrando en buy")
        print("___________________________________")
        symbol = request.form.get("symbol")
        item = lookup(symbol)
        print(item)

        if not symbol:
            return apology("Por  favor ingrese el simbolo")
        elif not item:
            return apology("Simbolo invalido")

        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("Los simbolos deben ser un entero postivo")

        except:
            return apology("Los simbolos deben ser positivos")

        user_id = session["user_id"]
        # usoid=? (es valido por el ide y lo uso para evitar poder id =:id)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        item_name = item["name"]
        item_price = item["price"]
        totalprice = item_price * shares

        if cash < totalprice:
            return apology("Dinero insuficiente")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id= ?", cash - totalprice, user_id)
            db.execute("INSERT INTO  transactiones (user_id,name,shares,price,type, symbol )VALUES(?,?,?,?,?,?)",
                       user_id, item_name, shares, item_price, 'buy', symbol)
        flash("!Compra Exitosa!")
        return redirect('/')
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactiones = db.execute("SELECT  type, symbol, price, shares, time FROM transactiones WHERE user_id = ?", user_id)

    return render_template("history.html", transactiones=transactiones, usd=usd)


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
        flash("!Sesión iniciada!")
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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        item = lookup(symbol)

        if not item:
            return apology("Simbolo invalido")

        return render_template("quoted.html", item=item, usd_function=usd)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if (request.method == "POST"):
        # declaracion de las variables
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Usuario incompleto", 400)

        elif not password:
            return apology("Ingrese una contraseña", 400)

        elif not confirmation:
            return apology("Ingrese una confirmación", 400)

        elif password != confirmation:
            return apology("contraseñas diferentes")

        hash = generate_password_hash(password)
        rows = db.execute("SELECT * FROM users WHERE username= ?", username)

        if len(rows):
            return apology("usuario existente ", 400)

        # consula la base de datos para verificar el usuario
        db.execute("INSERT INTO users (username, hash) VALUES (? , ?)", username, hash)
        return redirect("/")

        return apology("Usuario existente")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        user_id = session["user_id"]
        symbol = (request.form.get("symbol"))
        if symbol == None:
            return apology("No se encontró el símbolo", 400)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Los simbolos deben ser positivos", 400)

        if shares <= 0:
            return apology("Debe ser un numero positivo", 400)
        print("__________________________________--")
        print(symbol)

        shares_owned = db.execute(
            "SELECT SUM(shares) as total_shares FROM transactiones WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)
        print(shares_owned)

        if shares_owned[0]["total_shares"] <= 0 or shares_owned[0]["total_shares"] < shares:
            return apology("Usted no tiene sufientes acciones", 400)

        currentcash = db.execute("SELECT cash FROM users WHERE id= ?", user_id)

        itemname = lookup(symbol)["name"]
        itemprice = lookup(symbol)["price"]
        price = shares * itemprice
        db.execute("UPDATE users SET cash =? WHERE id = ?", currentcash[0]["cash"] + price, user_id)
        db.execute("INSERT INTO transactiones (user_id, name, shares, price, type, symbol) VALUES ( ? , ? , ? , ? ,? ,?)",
                   user_id, itemname, -shares, itemprice, "sell", symbol)
        flash("!Vendido!")
        return redirect("/")

    else:
        user_id = session["user_id"]
        symbols = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactiones WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0 ", user_id)
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
