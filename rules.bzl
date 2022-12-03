load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

def make_day(name):
    cc_library(
        name = str(name) + "-lib",
        hdrs = ["main.h"]
    )
    native.genrule(
        name = "download_input",
        srcs = [],
        outs = ["input"],
        cmd = "ls $@ || wget --header 'cookie: session=53616c7465645f5fe3fbfb7a6dc118199720e3a84cf85728886e70d8b5f0d4a97742644bb32cd49364b1a216038e7e009bf76b004082c90f453b339c24d014b0' https://adventofcode.com/2022/day/3/input && mv input $@"
    )

    cc_binary(
        name = "day" + str(name),
        srcs = ["main.cpp"],
        data = ["input"],
        deps = [":" + str(name) + "-lib"]
    )

