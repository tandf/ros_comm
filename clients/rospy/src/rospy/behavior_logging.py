import os
from rospy.core import get_name
from time import time
import string
import random

fileName = ""


def gen_random(length=12) -> str:
    return ''.join(random.choices(string.ascii_lowercase +
                                  string.digits, k=length))

def log(msg: str):
    if not os.getenv("ROS_ENABLE_BLOG"):
        return

    global fileName

    if not fileName:
        # Get log dir from env
        dir = "/home/yunpeng/robotics/gt-logging/out/"
        env = os.getenv("ROS_BLOG")
        if env:
            dir = env

        # Generate random file name
        random_str = gen_random()
        fileName = os.path.join(dir, f"{random_str}.txt")

        print(f"Blog file name: {fileName}")
        with open(fileName, "a+") as f:
            f.write(f"{get_name()} (py) open file\n")

    msg = f"[{int(time())}] {get_name()} {msg}"

    print(msg)
    with open(fileName, "a+") as f:
        f.write(msg + "\n")
