import sys

def insert_newlines(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            while len(line) > 110:
                outfile.write(line[:110] + '\n')
                line = line[110:]
            outfile.write(line)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <input_file> <output_file>")
    else:
        insert_newlines(sys.argv[1], sys.argv[2])
