import os
import glob

def make_snippets(prefix : str, body : str, description : str):
  res = ""
  prefix_format = f"\"prefix\":\"{prefix}\","
  body_format = f"\"body\":[\"{body}\"],"
  description_format = f"\"description\":\"{description}\""

  res = f"\"{prefix}\":{{{prefix_format + body_format + description_format}}},"

  return res


if __name__ == "__main__":
  cur = os.path.dirname(__file__)

  # cpp files
  files = glob.glob(cur+"/**/*.cpp", recursive = True)

  #snippets file
  snippets = cur + "/Snippets.txt"
  tmp = []

  for file in files:
    need = 0
    prefix = file[file.rfind("/")+1:file.rfind(".")]
    body = ""
    description = file[file.rfind("/")+1:file.rfind(".")]
    with open(file) as f:
      with open(snippets,mode = "w") as out:
        for line in f:
          if line.strip().startswith("//") and line.strip() != "//@@":
            continue
          if line.strip() == "//@@":
            need = 1 - need
            continue
          if need:
            body += repr(line)[1:-1]
        tmp.append(make_snippets(prefix, body, description))
  
  with open(snippets,mode = "w") as out:
    for snippet in tmp:
      out.write(snippet)
      out.write("\n")