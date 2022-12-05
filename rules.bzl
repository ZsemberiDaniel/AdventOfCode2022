load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

def make_day(name):
    cc_library(
        name = str(name) + "-lib",
        hdrs = ["main.h"]
    )
    native.genrule(
        name = "download_input",
        tools = ["//secrets:config.json"],
        outs = ["input"],
        cmd = "ls $@ || wget --header 'cookie: session='`cat $(location //secrets:config.json) | jq -r \".session\"` https://adventofcode.com/2022/day/" + str(name) + "/input && mv input $@"
    )

    cc_binary(
        name = "day" + str(name),
        srcs = ["main.cpp"],
        data = ["input"],
        deps = [
            ":" + str(name) + "-lib",
            "//utils:utils-lib"
        ]
    )

