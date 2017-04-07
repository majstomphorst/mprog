# helpers.py for mashup cs50 mother program application.py
# Programmeren 02 - pset 08 - exercise 01 
# By cs50
#
# the google news url is change to terun Dutch news
# theonion is unchanged to ensure compatibility

import os
import re
from flask import Flask, jsonify, render_template, request, url_for
from flask_jsglue import JSGlue

from cs50 import SQL
from helpers import lookup

LIMIT = 10

# configure application
app = Flask(__name__)
JSGlue(app)

# ensure responses aren't cached
if app.config['DEBUG']:
    @app.after_request
    def after_request(response):
        response.headers['Cache-Control'] = 'no-cache, no-store,\
        must-revalidate'
        response.headers['Expires'] = 0
        response.headers['Pragma'] = 'no-cache'
        return response

# configure CS50 Library to use SQLite database
db = SQL('sqlite:///mashup.db')


@app.route('/')
def index():
    '''Render map.'''
    if not os.environ.get('API_KEY'):
        raise RuntimeError('API_KEY not set')
    return render_template('index.html', key=os.environ.get('API_KEY'))


@app.route('/articles')
def articles():
    '''Look up articles for geo.'''

    # get geo location
    geo = request.args.get('geo')

    # check if geo has has a value
    if not geo:
        print('no geo')

    # return a json file with the articals
    return jsonify(lookup(geo))


@app.route('/search')
def search():
    '''Search for places that match query.'''

    # getting the search term from user
    place = request.args.get('q')

    # checking for number if its a number asume its a postal code
    if place.isdigit():

        location = db.execute('''SELECT * FROM places
                              WHERE postal_code = :place
                              OR postal_code LIKE :place2 LIMIT :LIMIT;''',
                              place=place, place2=place + '%', LIMIT=LIMIT)

    # if its not a postal code assumt its a city name
    else:

        location = db.execute('''SELECT * FROM places WHERE place_name = :place
                              OR place_name LIKE :place2 LIMIT :LIMIT;''',
                              place=place, place2=place + '%', LIMIT=LIMIT)

        # if you can find postal_code or city assume its a province
        if not location:

            location = db.execute('''SELECT * FROM places
                                  WHERE admin_name1 = :place OR admin_name1
                                  LIKE :place2 LIMIT :LIMIT;''',
                                  place=place, place2=place + '%', LIMIT=LIMIT)

    # checkking if location is found
    if not location:

        print('no found any!')

    return jsonify(location)


@app.route('/update')
def update():
    '''Find up to 10 places within view.'''

    # ensure parameters are present
    if not request.args.get('sw'):
        raise RuntimeError('missing sw')
    if not request.args.get('ne'):
        raise RuntimeError('missing ne')

    # ensure parameters are in lat,lng format
    if not re.search('^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$',
                     request.args.get('sw')):

        raise RuntimeError('invalid sw')
    if not re.search('^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$',
                     request.args.get('ne')):

        raise RuntimeError('invalid ne')

    # explode southwest corner into two variables
    (sw_lat, sw_lng) = [float(s) for s in request.args.get('sw').split(',')]

    # explode northeast corner into two variables
    (ne_lat, ne_lng) = [float(s) for s in request.args.get('ne').split(',')]

    # find 10 cities within view, pseudorandomly chosen if more within view
    if (sw_lng <= ne_lng):

        # doesn't cross the antimeridian
        rows = db.execute('''SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat
                          AND (:sw_lng <= longitude AND longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM() LIMIT 10''',
                          sw_lat=sw_lat, ne_lat=ne_lat,
                          sw_lng=sw_lng, ne_lng=ne_lng)

    else:

        # crosses the antimeridian
        rows = db.execute('''SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat
                          AND (:sw_lng <= longitude OR longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM() LIMIT 10''',
                          sw_lat=sw_lat, ne_lat=ne_lat,
                          sw_lng=sw_lng, ne_lng=ne_lng)

    # output places as JSON
    return jsonify(rows)
