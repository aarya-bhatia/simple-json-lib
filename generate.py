
types = ['object','array','string','number','null','boolean']
# suffix = ['create','free','clone']
# prefix = 'json'

with open('.functions.txt', 'w') as fout:
    for t in types:
        fout.write(f"json_{t}_t *json_{t}_create();\n")
        fout.write(f"json_{t}_t *json_{t}_clone(json_{t}_t *);\n")
        fout.write(f"void *json_{t}_free();\n")