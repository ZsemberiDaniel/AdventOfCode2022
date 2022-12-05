load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "utils-lib",
    data = ["//secrets:config.json"],
    hdrs = ["utils.hpp", "HTTPRequest.hpp"],
    deps = ["@jsoncpp_git//:jsoncpp"],
    visibility = ["//visibility:public"]
)
