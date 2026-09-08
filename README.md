# Technical Prep, 2026–2027

This workspace is for one locked target: become ready for Spring/Summer 2027 SWE internship interviews, then become a strong fit for ML/AI systems, infrastructure, inference, distributed-systems-adjacent, and protocol/blockchain infrastructure teams.

School and GPA are the first constraint. The plan is intentionally small enough to pause during heavy academic weeks and resume without a catch-up spiral.

## Do this today — Monday, 2026-08-31

Total cap: **3 hours 30 minutes**, including breaks. Do these in order.

### 1. Start the Python foundations course — 1 hour 45 minutes

Open [Harvard CS50P Lecture 0: Functions and Variables](https://www.youtube.com/watch?v=JP7ITIXGpHk). Watch the complete Lecture 0 and type every example yourself. Do not watch passively at 2× speed.

Today's topics are functions, variables, strings, integers/floats, parameters, return values, and reading error messages. This is the Python foundation course for the reset. It is about 16 hours total—not a random 24-hour marathon—and it will be spread across three weeks while you keep coding.

### 2. Open the systems textbook — 40 minutes

Get this exact edition:

> Randal E. Bryant and David R. O’Hallaron, *Computer Systems: A Programmer’s Perspective*, Third Edition, ISBN 978-0-13-409266-9.

Read **printed pages 1–13**, from the start of Chapter 1 through the end of Section 1.5, **“Caches Matter.”** If the PDF viewer's page counter is offset by the front matter, follow the printed page number on the page, not the viewer counter.

Stop at page 13. In a note, answer:

1. What happens between `hello.c` and an executable file?
2. Why is moving data often more expensive than arithmetic?
3. What problem does a cache solve?

### 3. Attempt the Day 1 Python file — 45 minutes

Open `python_prep/leetcode/day_001_practice_summary.py`.

- Work only in `summarize_scores`.
- Do not use AI, NumPy, pandas, `sum`, or `max` on the first attempt.
- Stop after 25 unaided minutes even if stuck; write the exact sticking point.
- Use the remaining time to debug and run the checks.
- The reference solution is separated at the bottom. Do not scroll to it until the timer ends.

Run your attempt with:

```bash
python3 python_prep/leetcode/day_001_practice_summary.py
```

Run the supplied reference only after your attempt:

```bash
python3 python_prep/leetcode/day_001_practice_summary.py --reference
```

### 4. Commit only the intended files — 20 minutes

This folder is connected to [`ryanjdorestal/prep`](https://github.com/ryanjdorestal/prep) on branch `main`.

Do **not** use `git add .` today: the repository also contains an untracked screenshot and the old unfinished `valid_parentheses.py`.

After filling in your Day 1 function:

```bash
cd /Users/ryandorestal/Desktop/prep
git status
git add README.md notes/BOOK_PLAN.md notes/DAILY_ROADMAP_2026-08-31_TO_2027-08-31.md python_prep/leetcode/day_001_practice_summary.py
git diff --cached
git commit -m "Add technical prep roadmap and day 1 Python practice"
git push origin main
```

Reading the cached diff before committing is mandatory. It confirms that your solution and only the intended planning files are being pushed.

## Foundation-course decision

Do **not** postpone coding until you have watched 48 hours of video.

- **Python:** use [CS50's Introduction to Programming with Python](https://cs50.harvard.edu/python/) as the full reset. Complete Lectures 0–5 over the first three weeks, including small exercises. Lectures 6–9 can follow as needed. Through 2026-09-20, these lectures and exercises **replace** the roadmap's Python interview blocks; they are not added on top.
- **C++:** starting Saturday 2026-09-05, use freeCodeCamp's [C++ Programming Course: Beginner to Advanced](https://www.youtube.com/watch?v=8jLOx1hD3_o). It is about 31 hours. During Fall, cover Chapters 2–12—basics through functions/returns—while compiling the examples. Skip the long environment-setup chapter except the macOS segment you actually need. Each course block replaces the roadmap's C++ block. Classes, ownership, and polymorphism come only after the fundamentals are stable.
- Every 45–60 minutes of video must produce a small file, test, explanation, or corrected bug. Video time without output does not count.

## NumPy and pandas decision

- **Today:** no NumPy and no pandas.
- **First 14 days:** core Python only—functions, conditionals, loops, strings, lists, dictionaries, exceptions, and tests.
- **Starting 2026-09-22:** do a selected **30 NumPy exercises**, three per week. Focus on array creation, shape, dtype, indexing, boolean masks, broadcasting, reductions, and vectorization.
- **Pandas:** do not grind “100 pandas exercises” now. Begin 15–20 targeted pandas/data-cleaning tasks with the Spring ML book. Pandas is useful, but it is not a priority for SWE interviews and it should not displace Python reasoning or NumPy.

The answer is therefore: **yes to a selected NumPy practice set after the Python reset; no to 100 NumPy plus 100 pandas exercises right now.**

## Start here

1. Open [`notes/DAILY_ROADMAP_2026-08-31_TO_2027-08-31.md`](notes/DAILY_ROADMAP_2026-08-31_TO_2027-08-31.md).
2. Do only today's line. If school is heavy, use the minimum version described below.
3. Use [`notes/BOOK_PLAN.md`](notes/BOOK_PLAN.md) to know what to read, what to skip, and what “finished” means.
4. On Sunday, mark the week `done`, `partial`, or `skipped for school`. Do not repay missed hours.

## Priority order

1. John Jay coursework, sleep, health, and existing research obligations
2. Python interview problem solving
3. The one active book
4. C++ rebuild, followed by deliberate Rust practice
5. ML/inference and systems artifacts
6. Blockchain specialization

If time collapses, preserve the highest item that still fits. Rust and projects are the first things to pause; GPA work never competes with a side-study deadline.

## Time caps

| Period | Normal cap | Exam/overload cap | Intent |
|---|---:|---:|---|
| Fall 2026 semester | 5–6 hours/week | 0–2 hours/week | Python interviews + systems/C++ |
| Winter break | 12–15 hours/week | 6 hours/week if taking a winter class | Distributed-systems concepts + Python + Rust start |
| Spring 2027 semester | 6–7 hours/week | 0–2 hours/week | Python interviews + ML foundations |
| Spring recess | 10–12 hours/week | 6 hours/week if coursework is due | ML consolidation + inference-service slice |
| Summer 2027 | 15–18 hours/week | 6–8 hours/week during a full-time internship/research load | Interview polish + inference/distributed/protocol depth |

The cap includes reading, coding, applications, and mocks. AFRL or Sator work that serves the week's learning goal **replaces** a project block; it never gets added on top.

## Minimum viable week

When classes become intense, do this and call the week successful:

- one 35-minute Python problem;
- one 45-minute active-book block;
- one 15-minute verbal review;
- everything else paused.

During the final-exam freezes in the roadmap, even this is optional.

## How the existing folders are used

| Existing path | Purpose in this plan |
|---|---|
| `python_prep/leetcode/` | Python interview solutions, tests, and short complexity notes |
| `python_prep/ml_snippets/` | NumPy-from-scratch ML ideas and small evaluation snippets |
| `python_prep/utils/` | Reusable local helpers only after a second real use appears |
| `c++_prep/leetcode/` | Selected solved problems rewritten in C++ for fluency—not a second grind |
| `c++_prep/systems/` | CS:APP exercises and small systems experiments |
| `c++_prep/pybind/` | Summer bridge work only if the inference service has a measured Python bottleneck |
| `rust_prep/book_exercises/` | Small ownership, borrowing, enum, trait, and error-handling exercises |
| `rust_prep/leetcode/` | A few already-known problems rewritten for language fluency |
| `rust_prep/mini_projects/` | One bounded protocol/parser or concurrent-worker artifact in Summer 2027 |
| `small_projects/inference_service/` | The single prep portfolio project; do not start another parallel project |
| `small_projects/other/` | Only tiny experiments that do not belong elsewhere |
| `notes/` | This roadmap, book plan, weekly explanations, mock notes, and trade-off writeups |

The existing unfinished `python_prep/leetcode/valid_parentheses.py` remains untouched. The smaller `day_001_practice_summary.py` is the first diagnostic; Valid Parentheses returns after the Python syntax reset.

## Problem-solving rule

For each interview problem:

1. Restate the input, output, constraints, and one edge case aloud.
2. Work unaided for 25 minutes.
3. Write the simplest correct solution, tests, and time/space complexity.
4. If blocked, study one hint or solution, close it, and reconstruct the code yourself.
5. Re-solve from a blank file 24–72 hours later.

AI may critique the explanation or tests after the attempt. It must not supply the first solution. The point is to make independent reasoning reliable.

## Integration rule for existing work

- **AFRL:** use a real required research task to practice typed data, provenance/lineage, deterministic experiments, baselines, evaluation metrics, and reproducibility. Do not copy sensitive or bulky research data into `prep`.
- **Sator:** when authorized Sator work overlaps the roadmap, use its real event-contract, replay/idempotency, durability, latency, observability, or inference boundary. Record the lesson in `notes/`; do not create a competing Sator implementation here.
- **Fourthorse:** remains dormant. This plan does not require reviving it.

## Completion scoreboard

Count distinct problems only after a clean unaided re-solve. Count a book chapter only after its stated output in the book plan exists.

| Date | Checkpoint |
|---|---|
| 2026-09-30 | 8–10 Python problems; arrays/hash/stack basics; CS:APP Chapters 1–2; C++ build/debug/STL baseline; resume and target-role language ready |
| 2026-10-31 | 18–22 Python problems; two pointers/sliding window/binary search/linked lists; CS:APP Chapters 3, 5, and most of 6; C++ RAII and ownership explanation |
| 2026-11-30 | 28–32 Python problems; trees/heaps/graphs; CS:APP through virtual memory and I/O; first 45-minute mock |
| 2026-12-21 | GPA protected through finals; 32–36 solid problems; CS:APP selected path complete or explicitly deferred without guilt |
| 2027-01-27 | 50–55 solid problems; DDIA selected path complete; two system-design one-pagers; Rust ownership/error-handling baseline; one full mock |
| 2027-03-31 | 65–70 solid problems; ML Chapters 1–6; linear/logistic regression and gradient descent NumPy snippets; evaluation vocabulary interview-ready |
| 2027-04-30 | 72–78 solid problems; ML through unsupervised learning; inference-service skeleton with tests, schema, health, and baseline latency |
| 2027-05-27 | 80–90 solid problems; ML Chapters 1–11 + selected appendices complete; three total mocks; school finals protected |
| 2027-06-30 | 95–105 solid problems; inference service v1 measured for latency/throughput; one real AFRL or Sator transfer note |
| 2027-07-31 | 110–120 solid problems; C++/Rust fluency artifact; Mastering Bitcoin through network/blockchain/consensus; two system-design mocks |
| 2027-08-31 | 120–130 deeply reviewed problems; six recent mocks; inference/protocol capstone explainable end to end; full readiness audit complete |

Problem count is a guardrail, not the objective. Being able to derive, test, explain, and re-solve matters more than collecting submissions.
