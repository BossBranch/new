#pragma once

enum class FilterResult : int {
    ShowPrioritized = 0,
    Show            = 1,
    Disable         = 2,
    Hide            = 3,
};