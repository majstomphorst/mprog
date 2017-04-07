# helpers.py for mashup cs50 mother program application.py
# Programmeren 02 - pset 08 - exercise 01 
# By cs50
#
# the google news url is change to terun Dutch news
# theonion is unchanged to ensure compatibility


import feedparser
import urllib.parse


def lookup(geo):
    '''Looks up articles for geo.'''

    # check cache for geo
    if geo in lookup.cache:
        return lookup.cache[geo]

    # get feed from Google
    feed = feedparser.parse('''http://news.google.nl/news?search?&geo={}
                            %2CNL&output=rss'''.
                            format(urllib.parse.quote(geo, safe='')))

    # if no items in feed, get feed from Onion
    if not feed['items']:
        feed = feedparser.parse('http://www.theonion.com/feeds/rss')

    # cache results
    lookup.cache[geo] = [{'link': item['link'], 'title':
                        item['title']} for item in feed['items']]

    # return results
    return lookup.cache[geo]

# initialize cache
lookup.cache = {}
