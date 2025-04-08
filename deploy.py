from flask import Flask, send_from_directory

app = Flask(__name__)
status: int = 1 # 0 is unlocked 1 is locked

@app.route("/")
def home():
    return send_from_directory("files", "index.html")

@app.route("/api/lock", methods=["POST"])
def lock():
    global status
    if status:
        print(f"Door is already locked")
    else:
        print(f"Locking the door")
    status = 1
    return {"status" : "locked"}, 200

@app.route("/api/unlock", methods=["POST"])
def unlock():
    global status
    if not status:
        print(f"Door is already unlocked")
    else:
        print(f"Unlocking door")
    status = 0
    return {"status" : "unlocked"}, 200

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000)
