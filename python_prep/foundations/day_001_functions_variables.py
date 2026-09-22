"""Python foundations — Day 1: functions and variables.

Watch CS50P Week 0 and type its examples before attempting this file.

Task
----
Implement ``make_receipt(item, price, quantity)``.

Return one string in this exact format:

    3 x notebook = $7.50

Rules
-----
* ``total`` must be calculated inside the function.
* Return the string; do not print it inside the function.
* Work from memory for 15 minutes before viewing the reference.
"""

import sys
from collections.abc import Callable


def make_receipt(item: str, price: float, quantity: int) -> str:
    """Return a one-line receipt summary."""
    raise NotImplementedError("Replace this line with your solution")


def run_checks(solution: Callable[[str, float, int], str]) -> None:
    assert solution("notebook", 2.50, 3) == "3 x notebook = $7.50"
    assert solution("pen", 1.25, 1) == "1 x pen = $1.25"
    assert solution("sticker", 0.50, 0) == "0 x sticker = $0.00"
    print("All Day 1 checks passed.")


# ---------------------------------------------------------------------------
# STOP. The reference is below. Do not read it before your 15-minute attempt.
# ---------------------------------------------------------------------------


def reference_make_receipt(item: str, price: float, quantity: int) -> str:
    total = price * quantity
    return f"{quantity} x {item} = ${total:.2f}"


if __name__ == "__main__":
    selected_solution = (
        reference_make_receipt if "--reference" in sys.argv else make_receipt
    )
    run_checks(selected_solution)
