# finance application.py
# Programmeren 02 - pset 07 - exercise 01
# By Maxim Stomphorst
# 
# NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE 
# NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE 
#
# Ik merk dat bij "sell" hij soms een paar seconden nodig heeft voordat hij index 
# goed laat zien. 
#
#
# NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE

from cs50 import SQL
from flask import Flask, flash, redirect, render_template
from flask import request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():

    # get current money
    money = db.execute("SELECT cash FROM users WHERE id = :user_id",
                        user_id = session["user_id"])
                        
    # make sure that if there is no money the site goes to login
    # if there is no money code crashes
    if not money:
        return  rdirect(url_for("login"))

    # lookup all users assets
    table = db.execute("SELECT * FROM assets WHERE id = :user_id",
                        user_id = session["user_id"])
    
    # creating a counter
    asset_value = 0
    
    # looking up currecnrt stock price
    for item in table:
        # looking up current stock price
        current_price = lookup(item["symbol"])
        # storing current stock price in table
        item["current_price"] = usd(current_price["price"])
        # calcuation current value of you assets
        item["current_value"] = usd(item["quantity"] * current_price["price"])
        # calcuation total asset value
        asset_value += float(item["current_value"].lstrip("$").replace(",", ""))
    
    # calculatng grand_total
    grand_total = asset_value + float(money[0]["cash"])
    
    # rendering template with the above value's 
    return render_template("index.html", table = table,
                            money = usd(float(money[0]["cash"])),
                            asset_value = usd(asset_value),
                            grand_total = usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    # if methode is POST
    if request.method == "POST":

        # check if user gave value's
        if request.form.get("buy_symbel") == "" or \
           request.form.get("number_to_buy") == "":
            return apology("Please check your input", 
                           "you symbol or the number field is empty")

        # check if user is trying to buy negative share's
        if int(request.form.get("number_to_buy")) < 1:
            return render_template("rick.html")

        # looking up stock data and check if stock exists
        stock = lookup(request.form["buy_symbel"])
        if not stock:
            return apology("stock not found")
        
        # lookup users current credit   
        credit = db.execute("SELECT cash FROM users WHERE id = :user_id",
                             user_id = session["user_id"])

        # check if customer has enough money to buy the stock
        if not float(stock['price']) * float(request.form.get("number_to_buy")) <\
               float(credit[0]["cash"]):
            return apology("you credit is not high enough")
            
        # update transactions with what is happening
        db.execute("""INSERT INTO transactions 
                   (id, bought_sold, symbol, quantity, price)
                   VALUES (:user_id, :bought_sold, :symbol, :quantity, :price)""",
                   user_id = session["user_id"], bought_sold = "bought",
                   symbol = stock['symbol'], 
                   quantity = int(request.form.get("number_to_buy")),
                   price = float(stock['price']))
            
        # looking up users stock holdings
        excist = db.execute("""SELECT * FROM assets WHERE 
                            id = :user_id AND symbol = :symbol""",
                            user_id = session["user_id"], 
                            symbol = stock['symbol'])
            
        # if the stock is not jet owned add it to assets
        if not excist:
            db.execute("""INSERT INTO assets (id, symbol, quantity)
            VALUES (:user_id, :symbol, :quantity)""",
            user_id = session["user_id"], symbol = stock['symbol'], 
            quantity = int(request.form.get("number_to_buy")))
            print(int(request.form.get("number_to_buy")))
        # if the stock is allready owned mutate the quantity
        else:    
            db.execute("""UPDATE assets SET quantity = quantity + :quantity
                        WHERE id = :user_id AND symbol = :symbol""",
                        quantity = int(request.form.get("number_to_buy")),
                        user_id = session["user_id"], symbol = stock['symbol'])
            
        # calculation new users cash
        new_cash = credit[0]['cash'] - (int(request.form.get("number_to_buy")) * \
                   stock['price'])
            
        # update user's cash 
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                    cash = new_cash, user_id = session["user_id"])
        
        # display index
        return redirect(url_for("index"))
    
    # if methode is GET     
    else:
        return render_template("buy.html")
    

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    # looking up all users data in multipul tables
    info = db.execute("""SELECT date, bought_sold, symbol, quantity, price
                      FROM users JOIN transactions 
                      ON users.id = transactions.id 
                      WHERE users.id = :user_id""", 
                      user_id = int(session["user_id"]))

    # converting "price" to $"price.xx" estathixs 
    for data in info:
        data["price"] = usd(data["price"])
    
    # rendering history with the data collected
    return render_template("history.html", info = info)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                           username = request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    # if website methode POST
    if request.method == "POST":

        # looking up stock data and check if stock exists
        stock = lookup(request.form["stock_symbel"])
        if not stock:
            return apology("stock not found")

        # if stock found display the data
        return render_template("quoted.html", name = stock['name'], 
                                price = usd(stock['price']),
                                symbol = stock['symbol'])

    # if methode is GET 
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    # if information is send check form if not correct apology
    if request.method == "POST":
        
        # check if user gave a username and password
        if request.form["username"] == "" or request.form["password"] == "":
            return apology("username or and paasword blank!")
        
        # check if passwords are the same
        if request.form["password"] != request.form["password2"]:
            return apology("password's downt maths")
        
        # query database for username
        usercheck = db.execute("SELECT * FROM users WHERE username = :username",
                                username = request.form.get("username"))

        # ensure username exists
        if len(usercheck) == 1:
            return apology("username already in use")
            
        # register in database    
        db.execute("""INSERT INTO users (username, hash)
                   VALUES(:username, :password)""",
                   username = request.form["username"],
                   password = pwd_context.encrypt(request.form["password"]))
        
        # extrack form database the user's id and give it to index ass session 
        user_id = db.execute("SELECT id FROM users WHERE username = :username",
                             username = request.form.get("username"))
        
        # remember which user has logged in
        session["user_id"] = user_id[0]["id"]

        return redirect(url_for("index"))
        
    # is users ask for pages via GET give them the page
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    
    # if methode is POST
    if request.method == "POST":
        
        # check if user gave value's 
        if request.form.get("sell_symbel") == "" or \
           request.form.get("number_to_sell") == "":
            return apology("EMPTY or negative to sell")
            
        # check if user is trying to sell negative shar's
        if int(request.form.get("number_to_sell")) < 1:
            return render_template("rick.html")
        
        # looking up stock in users assets 
        excist = db.execute("""SELECT * FROM assets 
                            WHERE id = :user_id AND symbol = :symbol 
                            AND quantity >= :quantity""",
                            user_id = session["user_id"], 
                            symbol = request.form.get("sell_symbel"), 
                            quantity = request.form.get("number_to_sell"))

        # checking if users has the stock 
        if not excist:
            return apology("you have no stock") 

        # lookup stock pricing and user's current credit
        stock = lookup(request.form["sell_symbel"])
        credit = db.execute("SELECT cash FROM users WHERE id = :user_id", 
                            user_id = session["user_id"])

        # update transactions with what is happening
        db.execute("""INSERT INTO transactions (id, bought_sold, symbol,
                   quantity, price) VALUES (:user_id, :bought_sold, :symbol,
                   :quantity, :price)""", 
                   user_id = session["user_id"], bought_sold = "sold", 
                   symbol = stock['symbol'], 
                   quantity = int(request.form.get("number_to_sell")), 
                   price = float(stock['price']))
            
        # if you stock possession is 0 delete record (after stelling)
        if excist[0]["quantity"] == int(request.form.get("number_to_sell")):
            db.execute("""DELETE FROM assets WHERE id = :user_id 
                       AND symbol = :symbol""", 
                       user_id = session["user_id"], 
                       symbol = stock['symbol'])

        # update assets
        db.execute("""UPDATE assets SET quantity = quantity - :quantity 
                   WHERE id = :user_id AND symbol = :symbol""", 
                   quantity = int(request.form.get("number_to_sell")), 
                   symbol = stock['symbol'], user_id = session["user_id"])
            
        # calculation new user's cash
        new_cash = credit[0]['cash'] + (int(request.form.get("number_to_sell")) * \
                   stock['price'])
        
        # update user's cash 
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
        cash = new_cash, user_id = session["user_id"])
        
        # display index
        return render_template("index.html")
        
    # if methode is GET
    else:
        return render_template("sell.html")


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    """allows the user to change there password"""
    
    # if metode is POST
    if request.method == "POST":
        
        # check if fields arent empty
        if request.form.get("new_password") == "" or \
           request.form.get("new_password_verification") == "":
               return apology("one or more fields are empty")

        # check if passwords math
        if not request.form.get("new_password") == \
               request.form.get("new_password_verification"):
                   return apology("password's downt match")
            
        db.execute("UPDATE users SET hash = :password WHERE id = :user_id", 
                   password = pwd_context.encrypt(request.form.get("new_password")),
                   user_id = session["user_id"])

        # return to index
        return render_template("index.html")

    # if methode is GET
    else:
        # check if old password is correct
        return render_template("change.html")
