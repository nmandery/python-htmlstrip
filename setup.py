#!/usr/bin/env python 

from distutils.core import setup, Extension, Command
from unittest import TextTestRunner, TestLoader

class TestCommand(Command):
    user_options = []
    
    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        import tests
        loader = TestLoader()
        t = TextTestRunner()
        t.run(loader.loadTestsFromModule(tests))


setup(
    name="htmlstrip",
    version="0.1",
    description="a simple c module to strip whitespace from html",
    ext_modules=[
        Extension("htmlstrip", ["src/htmlstrip.c"])
        ],
    cmdclass = {
        "test": TestCommand
        }
    )

