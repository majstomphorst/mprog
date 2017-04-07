import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positive_set = []
        self.negative_set = []

        # make this a function
        file_pos = open(positives, "r")
        for line_pos in file_pos.readlines():
            # read_line = file.readline() 
            if not line_pos.startswith(";") or line_pos.startswith(" "):
                self.positive_set.append(line_pos.rstrip("\n"))
        file_pos.close()

        # make this a function      
        file_neg = open(negatives, "r")
        for line_neg in file_neg.readlines():
            # read_line = file.readline() 
            if not line_neg.startswith(";") or line_neg.startswith(" "):
                self.negative_set.append(line_neg.rstrip("\n"))
        file_neg.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
            #counting 
        positive_count = 0
        negative_count = 0 
        neutral = 0
        
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        
        for token in tokens:
            token = token.lower()
            if token in self.positive_set:
                positive_count += 1
            elif token in self.negative_set:
                negative_count += 1
            else:
                neutral += 1
        
        return positive_count - negative_count 
