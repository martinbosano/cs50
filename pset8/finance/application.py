import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    ## first checks
    if request.method == "POST":
        if request.form["symbol"] == "":
            return apology("You must provide a symbol")
        stock = lookup(request.form["symbol"])
        if not stock:
            return apology("There is no such stock")
        if int(request.form['shares']) < 0:
            return apology("You have to provide a positive integer")
        if request.form['shares'] == 0:
            return apology("You can't buy cero shares")

        available_cash = (db.execute("SELECT cash FROM users WHERE id = :id", id = session['user_id']))
        cash = float(available_cash[0]['cash'])
        stock_purchased = request.form['symbol']
        price = float(stock['price'])
        amount = int(request.form['shares'])
        transaction_price = float(price * amount)
        time = datetime.now()
        if cash < transaction_price:
            return apology("You don't have the necessary amount of cash to execute the transaction")
            ###update databases
        else: 
            db.execute("UPDATE users SET cash = (cash - :transaction_price) WHERE id = :user_id", transaction_price = transaction_price, user_id=session["user_id"])
            db.execute("INSERT INTO purchases (user_id, stock_purchased, amount_purchased, price, date) VALUES (:user_id, :stock_purchased, :amount_purchased, :price, :date)", user_id= session['user_id'], stock_purchased = stock_purchased, amount_purchased = amount, price = price, date = time)
            flash("Done!")
            return redirect("/index.html")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions""" #hacerrrr
    return apology("TODO")


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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    ####### toquetear éstooooooo
    if request.method == "POST":
        if request.form["symbol"] == "":
            return apology("You must provide a symbol")
        stock = lookup(request.form["symbol"])
        if not stock:
            return apology("There is not such symbol")
        else:
            return render_template("quoted.html", stock = stock)
    elif request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # User reached route via POST
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("You must provide an username")
        if request.form.get("username") == ' ':
            return apology("You can't use blank spaces in the username field")
        if not request.form.get("password"):
            return apology("You must provide a password")
        if request.form.get("password") == ' ':
            return apology("You can't use blank spaces in the password field")
        if request.form.get("password confirmation") != request.form.get("password"):
            return apology("Your passwords doesn't match")
        if request.form.get("password confirmation") == ' ':
            return apology("You can't use blank spaces in the password confirmation field")
        password = request.form.get("password");
        password = generate_password_hash(password)
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = request.form.get("username"), hash = password);
        if not result:
             return apology("That username already exists")


        ### VER SI VALE LA PENA PEDIR CONTRASEÑAS FUERTES

       # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

    """Register user"""
    return apology("User succesfully registered")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
