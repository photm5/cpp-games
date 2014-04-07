import pathlib

class FileMissingError(Exception):
    def __init__ (self, path_to_file):
        self.path_to_file = path_to_file

    def __str__ (self):
        return "File " + self.path_to_file + " doesn't exist!"


class Target:
    def __init__ (self, output_path):
        self.output_path = output_path

    def __str__ (self):
        return str(self.output_path)

    def make (self):
        if not self.output_path.exists(): # Just make sure the file exists
            raise FileMissingError(self.output_path)

    def check_mustbemade (self):
        if not self.output_path.exists(): # Just make sure the file exists
            raise FileMissingError(self.output_path)
        return False

    def get_mtime (self):
        return self.output_path.stat().st_mtime

class CompiledObject(Target):
    def __init__ (self, source_targets, output_path, compiler):
        Target.__init__(self, output_path)
        self.source_targets = source_targets
        self.compiler = compiler
        self.output_path = pathlib.Path(self.output_path)

    def check_mustbemade (self):
        try:
            output_mtime = self.get_mtime()
        except FileNotFoundError:
            return True
        for target in self.source_targets:
            if target.check_mustbemade():
                return True
            if target.get_mtime() > output_mtime:
                return True
        return False

    def make (self):
        sources = " ".join( str(elem) for elem in self.source_targets )
        self.compiler(sources, str(self.output_path))

from overlay import *
