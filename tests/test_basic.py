import htmlstrip
import unittest

TEST_STRING = u"""
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

class TestBasic(unittest.TestCase):
    def test_simpledoc(self):
        shtml = htmlstrip.strip(TEST_STRING)
        self.assertTrue(shtml != None, "strip returned None")
        self.assertTrue(len(shtml) < len(TEST_STRING), "compressed sting is not smaller")
