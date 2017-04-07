from flask import Flask, redirect, render_template, request, url_for

import os
import sys
import helpers
from analyzer import Analyzer


app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))
        
    # get screen_name's tweets if screen_name doesn't exist return to index page
    tweets = helpers.get_user_timeline(screen_name,100)
    if tweets == None:
        return redirect(url_for("index"))
    
    # making list with positive and negative words
    positives_txt = os.path.join(sys.path[0], "positive-words.txt")
    negatives_txt = os.path.join(sys.path[0], "negative-words.txt")
    
    # loading dictionary files to memory
    analyzer = Analyzer(positives_txt, negatives_txt)
    
    # keeping track of tweets score's
    positive = 0
    negative = 0
    neutral = 0
    
    for tweet in tweets:
        score = analyzer.analyze(tweet)
        if score > 0:
            positive += 1
        elif score < 0:
             negative += 1
        else:
            neutral += 1   
            
    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
