"""Day 1 Python foundations: summarize practice scores.

Your task
---------
Implement ``summarize_scores(scores)``.

``scores`` is a list of integer percentages. Return a dictionary containing:

* ``attempts``: number of scores
* ``passed``: number of scores greater than or equal to 70
* ``average``: arithmetic mean as a float
* ``best``: highest score, or ``None`` when the list is empty

First-attempt rules
-------------------
* Use a loop and an ``if`` statement.
* Do not use NumPy, pandas, collections.Counter, sum, or max.
* Work unaided for 25 minutes.
* State the time and space complexity before viewing the reference solution.

Examples
--------
``summarize_scores([90, 65, 75, 80])`` should return::

    {
        "attempts": 4,
        "passed": 3,
        "average": 77.5,
        "best": 90,
    }

``summarize_scores([])`` should return::

    {
        "attempts": 0,
        "passed": 0,
        "average": 0.0,
        "best": None,
    }
"""


"First attempt:"

""" [CODE BLOCK START]"""

#Defining the variables part of the assignment 

float attempts;

float passed 

float average; 

float best;

scores = []

#function summarizing scores
def summarize_score(scores) {

sum_of_scores =

float attempts = len(scores);

float passed 

float average; 

float best;

if scores == [] {

    print(""" attempts: 0, passed: 0, average: 0, best: 0 """)
} else {

  print("attempts: " attempts);
  print("passed: " passed);
  print("average: " average);
  print("best: " best);

}

}

"""

[END OF CODE BLOCK]
continue tmr : (
"""
from collections.abc import Callable
import sys


Summary = dict[str, int | float | None]


def summarize_scores(scores: list[int]) -> Summary:
    """Return attempts, passes, average, and best score.

    Replace the exception with your implementation.
    """
    raise NotImplementedError("Implement summarize_scores before running the checks")


def run_checks(solution: Callable[[list[int]], Summary]) -> None:
    """Run a small, readable check suite against a supplied solution."""
    cases = [
        (
            [90, 65, 75, 80],
            {"attempts": 4, "passed": 3, "average": 77.5, "best": 90},
        ),
        (
            [],
            {"attempts": 0, "passed": 0, "average": 0.0, "best": None},
        ),
        (
            [70],
            {"attempts": 1, "passed": 1, "average": 70.0, "best": 70},
        ),
        (
            [20, 30, 40],
            {"attempts": 3, "passed": 0, "average": 30.0, "best": 40},
        ),
    ]

    for scores, expected in cases:
        actual = solution(scores)
        assert actual == expected, (
            f"For scores={scores}, expected {expected}, but received {actual}"
        )

    print("All Day 1 checks passed.")


# ============================================================================
# STOP. THE REFERENCE SOLUTION IS BELOW.
# Do not continue until your 25-minute unaided attempt and complexity note exist.
# ============================================================================


def reference_summarize_scores(scores: list[int]) -> Summary:
    """Reference implementation: O(n) time and O(1) auxiliary space."""
    attempts = 0
    passed = 0
    total = 0
    best: int | None = None

    for score in scores:
        attempts += 1
        total += score

        if score >= 70:
            passed += 1

        if best is None or score > best:
            best = score

    average = total / attempts if attempts > 0 else 0.0

    return {
        "attempts": attempts,
        "passed": passed,
        "average": average,
        "best": best,
    }


if __name__ == "__main__":
    selected_solution = (
        reference_summarize_scores if "--reference" in sys.argv else summarize_scores
    )
    run_checks(selected_solution)
