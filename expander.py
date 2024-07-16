import re
import os
import argparse
from pathlib import Path

include_my_file = re.compile('#include\s*["]((.*)(|.hpp))["]\s*')
include_std_file = re.compile('#include\s*[<]((.*)(|.hpp))[>]\s*')

include_guard = re.compile('#.*_HPP')
ignore = re.compile('(#include\s*<bits/stdc\+\+.h>|using\s*namespace\s*std;)')

current_dir = Path.cwd()

defined = set()

def dfs(file : str, type : str) -> list:
  if type == "std":
    if file in defined:
      return []
    else:
      defined.add(file)
      std.append("#include <" + file + ">")
      return []

  dir = os.path.dirname(file)
  base = os.path.basename(file)

  if base in defined:
    return []

  s = open(str(current_dir / file)).read()

  defined.add(base)

  for line in s.splitlines():
    if include_guard.match(line) or ignore.match(line): 
      continue

    if include_std_file.match(line):
      Included = include_std_file.match(line)
      dfs(Included.group(1), "std")
    elif include_my_file.match(line):
      Included = include_my_file.match(line)
      dfs(dir + "/" + Included.group(1), "my")
    else:
      tmp.append(line)

if __name__ == "__main__":
  parser = argparse.ArgumentParser(description = "Expander")
  parser.add_argument("source", help = "Source File")

  args = parser.parse_args()

  s = open(args.source).read()

  tmp = []
  std = []
  result = []
  for line in s.splitlines():

    if ignore.match(line):
      tmp.append(line)
    elif include_std_file.match(line):
      Included = include_std_file.match(line)
      dfs(Included.group(1), "std")
    elif include_my_file.match(line):
      Included = include_my_file.match(line)
      dfs(Included.group(1), "my")
    else:
      tmp.append(line)
      
  result = std + result

  for r in tmp:
    if r == "" and len(result) > 1 and result[-1] == "" :
      continue
    result.append(r)

  for r in result:
    print(r)
