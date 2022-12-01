load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

def make_day(name):
    cc_library(
        name = str(name) + "-lib",
        hdrs = ["main.h"]
    )

    cc_binary(
        name = "day" + str(name),
        srcs = ["main.cpp"],
        data = ["input.txt"],
        deps = [":" + str(name) + "-lib"]
    )

