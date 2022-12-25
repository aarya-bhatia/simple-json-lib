types = ['base','object','array','string','number','boolean']

with open('.functions.txt', 'w') as fout:
    for t in types:
        fout.write(f"json_{t}_t *json_{t}_create();\n")
        fout.write(f"json_{t}_t *json_{t}_clone(json_{t}_t *);\n")
        fout.write(f"void json_{t}_free(json_{t}_t *);\n")
        fout.write(f"String *json_{t}_to_string(json_{t}_t *);\n")
        # fout.write(f"json_{t}_t *json_{t}_parse(String *);\n")
        fout.write("\n")