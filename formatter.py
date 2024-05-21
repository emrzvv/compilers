import sys

def replace_tabs_and_insert_newlines(input_file, output_file, lang=None):
    tab_replacement = ' ' * 4 if lang != 'scala' else ' ' * 2

    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            line = line.replace('\t', tab_replacement)  # Заменяем табуляции
            while len(line) > 110:
                outfile.write(line[:110] + '\n')
                line = line[110:]
            outfile.write(line)

if __name__ == "__main__":
    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print("Usage: python script.py <input_file> <output_file> [scala]")
    else:
        input_file = sys.argv[1]
        output_file = sys.argv[2]
        lang = sys.argv[3] if len(sys.argv) == 4 else None
        replace_tabs_and_insert_newlines(input_file, output_file, lang)
