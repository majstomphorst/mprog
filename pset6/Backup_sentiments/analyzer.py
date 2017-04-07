import nltk
import sys

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        # creating a dictionary to store word (key) and ther intention (value) 
        self.dic = {}

        # list of word's too memory positive words get value 1 and negatives -1
        load_dictionary (self, positives, 1)
        load_dictionary (self, negatives, -1)

    def analyze(self, tweet):
        """Analyze text for sentiment, returning its score."""
        
        # keeping track of the score 
        score = 0
        
        # filtering though tweets exstracting the useful words
        # preserve_case = false maks them lowercase 
        tokenizer = nltk.tokenize.TweetTokenizer(preserve_case = False)
        tokens = tokenizer.tokenize(tweet)
        
        # checking word for word the intension and keeping score
        for word in tokens:
            if word in self.dic:
                if self.dic[word] == 1:
                    score += 1
                else:
                     score -= 1
      
        return score

def load_dictionary (self, dictionary, value):
    """Loading a file.txt into memory (dictionary)"""
    
    file = open(dictionary, "r")
    if file == None:
        sys.exit("Opening dictionary file fialed")
    for line in file.readlines():
        if not line.startswith(";") or line.startswith(" "):
            self.dic[line.rstrip("\n")] = value
    file.close()
