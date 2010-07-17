import htmlstrip
import unittest

SIMPLEDOC_STRING = u"""
<html>
    <head>
    </heady>

    <body>
        <h1>heading</h1>
        Lorem ipsum dolor 
        sit amet, consetetur sadipscing elitr, sed diam 
                        nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, 
        sed diam voluptua. At vero eos et accusam et 



        justo duo dolores et ea rebum. Stet clita kasd                          gubergren,
        no sea takimata                                     sanctus est Lorem ipsum dolor sit amet. Lorem 
        ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod 
        tempor invidunt ut labore et dolore magna 
        

                        aliquyam erat, sed diam voluptua. 
    </body>
</html>
"""

HTMLCOMMENT_STRING = u"""
<html>
<!--[if IE] comment_should_stay []-->
<should_be_there/>
    <!-- should_not_be_there --> 
    should_be_there_too
<should_also_be_there/>
</html>

"""

class TestBasic(unittest.TestCase):
    def test_simpledoc(self):
        shtml = htmlstrip.strip(SIMPLEDOC_STRING)
        self.assertTrue(shtml != None, "strip returned None")
        self.assertTrue(len(shtml) < len(SIMPLEDOC_STRING), "compressed sting is not smaller")

    def test_htmlcomment(self):
        shtml = htmlstrip.strip(HTMLCOMMENT_STRING)
        self.assertTrue(shtml.find("should_be_there") != -1, "deleted to much")
        self.assertTrue(shtml.find("should_also_be_there") != -1, "deleted to much")
        self.assertTrue(shtml.find("should_be_there_too") != -1, "deleted to much")
        self.assertTrue(shtml.find("comment_should_stay") != -1, "deleted browser switch")
        self.assertTrue(shtml.find("should_not_be_there") == -1, "did not delete comment")
