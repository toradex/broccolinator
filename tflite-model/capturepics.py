import sys
import requests
import time

for counter in range(0, 25):

    for i in range(1, 5):
        print(str(i))
        time.sleep(1)

    filename = "images/" + sys.argv[1] + "/" + str(counter) + ".jpg"

    r = requests.get("http://192.168.1.3/image/jpeg.cgi")
    open(filename, "wb").write(r.content)
    print(f"captured {counter}")
