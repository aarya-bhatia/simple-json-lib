types = ['null','object','array','string','number','boolean']

with open('.functions.txt', 'w') as fout:
    for t in types:
        fout.write(f"void *{t}_default_constructor();\n")
        fout.write(f"void *{t}_copy_constructor(void * elem);\n")
        fout.write(f"void {t}_destructor(void * elem);\n")
        fout.write("\n")

