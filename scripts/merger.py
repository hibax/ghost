import os
import re
import sys


#excluded_files = ["main.cpp"]
excluded_files = []

include_regex = r"#include \"([\w\.]+)\""

processed_files = []


def run():

    working_dir = sys.argv[1]

    if not os.path.exists(working_dir):
        print "Path does not exist : " + working_dir
        return
    else:
        src_dir = os.path.join(working_dir, "src")
        if not os.path.exists(src_dir):
            print "Path does not exist : " + src_dir
            return
        output_dir = os.path.join(working_dir, "generated_src")
        output_file = os.path.join(output_dir, "codingame.cpp")

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        # clean
        with open(output_file, "w") as output:
            output.write("")
        #process_file(os.path.join(src_dir, "main.cpp"), False, output_file)
        process_dir(src_dir, output_file)


def process_dir(src_dir, output_file):
    files = [f for f in os.listdir(src_dir) if os.path.isfile(os.path.join(src_dir, f))]

    for file in files:
        if file not in excluded_files:
            process_file(os.path.join(src_dir, file), False, output_file)


def process_file(file, is_included, output_file):
    if file.endswith(".h") and not is_included:
        return
    elif file.endswith(".cpp"):
        print "Processing " + file
        with open(output_file, "a") as output:
            output.write("/*-- File: " + file + " start --*/\n")
    elif file.endswith(".h"):
        print "Including " + file
        with open(output_file, "a") as output:
            output.write("/*-- #include \"" + file + "\" start --*/\n")
    else:
        print "Ignoring " + file

    if file not in processed_files:

        with open(file, "r") as input:
            for line in input:
                if line.startswith("#include \""):
                    m = re.match(include_regex, line)
                    if m:
                        included_file = os.path.join(os.path.dirname(file), m.group(1))
                        print "Found a file to include : " + included_file
                        process_file(included_file, True, output_file)
                    else:
                        print "warning : " + line
                elif line.startswith("#pragma once"):
                    processed_files.append(file)
                else:
                    with open(output_file, "a") as output:
                        output.write(line)


    if file.endswith(".cpp"):
        with open(output_file, "a") as output:
            output.write("/*-- File: " + file + " end --*/\n")
    elif file.endswith(".h"):
        with open(output_file, "a") as output:
            output.write("/*-- #include \"" + file + "\" end --*/\n")


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "Usage : merger.py path_to_project"
        print "Example : merger.py D:/git-workspace/toto"
    else:
        run()
