import os
import glob

if __name__ == "__main__":
  cur = os.path.dirname(__file__)

  # cpp files
  files = glob.glob(cur+"/**/*.cpp", recursive = True)

  for file in files:
    with open(file) as f:
      pass
  