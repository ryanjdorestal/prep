# Minimal Book Plan

There are four books and never more than one active book. C++, Rust, and interview algorithms use coding practice and official references, not additional cover-to-cover books.

## Sequence at a glance

| Dates | Active book | Mode | Required output |
|---|---|---|---|
| 2026-08-31 to 2026-12-06 | *Computer Systems: A Programmer’s Perspective*, 3rd ed. | Deep study, 3 hours/week | Systems explanations + small C++ experiments |
| 2026-12-26 to 2027-01-24 | *Designing Data-Intensive Applications*, 2nd ed. | Conceptual, break pace | Two system-design one-pagers + verbal trade-off review |
| 2027-01-28 to 2027-05-16 | *Hands-On Machine Learning with Scikit-Learn and PyTorch*, 1st ed. | Deep study, 3–4 hours/week | NumPy snippets + end-to-end ML work + inference-service foundation |
| 2027-06-28 to 2027-08-15 | *Mastering Bitcoin*, 3rd ed. | Conceptual/technical, summer pace | Transaction/block parser + protocol/security explanations |

Official edition references: [CS:APP](https://www.pearson.com/en-us/subject-catalog/p/computer-systems-a-programmer-s-perspective/P200000003479/9780134092669), [DDIA](https://www.oreilly.com/library/view/designing-data-intensive-applications/9781098119058/), [Hands-On ML with PyTorch](https://www.oreilly.com/library/view/hands-on-machine-learning/9798341607972/), and [Mastering Bitcoin](https://www.oreilly.com/library/view/mastering-bitcoin-3rd/9781098150082/).

## 1. Fall 2026 — systems foundation

**Exact title:** *Computer Systems: A Programmer’s Perspective, Third Edition*  
**Authors:** Randal E. Bryant and David R. O’Hallaron  
**ISBN-13:** 9780134092669

### Required path

- Chapter 1, **A Tour of Computer Systems** — program lifecycle and the whole-stack mental model.
- Chapter 2, **Representing and Manipulating Information** — bits, integers, floating point, overflow, shifts.
- Chapter 3, **Machine-Level Representation of Programs** — registers, stack frames, control flow, procedures, data layout.
- Chapter 5, **Optimizing Program Performance** — measurement, locality, compiler limits, dependency chains.
- Chapter 6, **The Memory Hierarchy** — cache structure, locality, misses, cache-friendly code.
- Chapter 7, **Linking** — symbols, object files, static/dynamic linking, libraries.
- Chapter 8, **Exceptional Control Flow** — processes, context switches, signals, process control.
- Chapter 9, **Virtual Memory** — address translation, paging, allocation, memory mapping.
- Chapter 10, **System-Level I/O** — file descriptors, robust I/O, metadata, sharing.
- Chapter 11, **Network Programming** — client/server model, sockets, DNS, basic web serving.
- Chapter 12, **Concurrent Programming** — processes, I/O multiplexing, threads, synchronization, races.

### Skip or skim

- Skim Chapter 4, **Processor Architecture**. Know pipelining and hazards conceptually; do not spend the semester implementing the textbook processor.
- Do representative exercises, not every exercise or lab.

### Completion test

Without notes, explain: source-to-executable flow; stack vs. heap; cache locality; static vs. dynamic linking; process vs. thread; virtual memory; file descriptors; a TCP request; race, mutex, deadlock, and semaphore. Demonstrate at least four ideas in `c++_prep/systems/` and connect one idea to a real Sator or AFRL concern.

## 2. Winter 2026–27 — distributed/data systems

**Exact title:** *Designing Data-Intensive Applications, Second Edition*  
**Authors:** Martin Kleppmann and Chris Riccomini  
**ISBN-13:** 9781098119058

Use the 2026 second edition, not the first edition.

### Required path

- Chapters 1–2 — architectural trade-offs; latency, reliability, scalability, maintainability.
- Chapter 4 — storage/retrieval, B-trees vs. LSM trees, row vs. column orientation.
- Chapter 5 — encoding/evolution, schemas, REST/RPC, workflows, event-driven systems.
- Chapters 6–7 — replication, lag, conflict, leader models, sharding, hotspots, rebalancing.
- Chapters 8–10 — transactions, partial failure, clocks/timeouts, consistency, logical clocks, consensus.
- Chapters 11–13 — batch/stream processing, event logs, time, fault tolerance, correctness and end-to-end arguments.

### Skip or skim

- Skim Chapter 3 unless a current project needs a data-model decision.
- Skip Chapter 14 for this sprint; return later for ethics/privacy context.
- No distributed database project during winter. The goal is reasoning, not another codebase.

### Completion test

Create two one-page designs in `notes/`: one for a durable/replayable Sator event path and one for an ML inference request/logging path. Each must state load, SLOs, failure modes, data model, consistency needs, idempotency, backpressure, and rejected alternatives. Explain replication vs. sharding, at-least-once vs. exactly-once effects, and why timeouts cannot prove failure.

## 3. Spring 2027 — ML and deep-learning foundation

**Exact title:** *Hands-On Machine Learning with Scikit-Learn and PyTorch*  
**Author:** Aurélien Géron  
**Edition:** First edition, October 2025  
**ISBN:** 9798341607972

This deliberately replaces the earlier TensorFlow choice. It preserves the classical ML sequence while using PyTorch and Hugging Face, and its quantization appendix maps better to the target inference roles.

### Required path

- Chapter 1, **The Machine Learning Landscape** — problem types, data mismatch, over/underfitting, validation, deployment issues.
- Chapter 2, **End-to-End Machine Learning Project** — framing, splits, preprocessing, pipelines, cross-validation, tuning, error analysis.
- Chapter 3, **Classification** — confusion matrix, precision/recall, ROC, thresholds, multiclass and multilabel evaluation.
- Chapter 4, **Training Models** — linear/logistic regression, gradient descent, regularization, learning curves.
- Chapter 5, **Decision Trees** — splitting, impurity, regularization, instability.
- Chapter 6, **Ensemble Learning and Random Forests** — bagging, boosting, stacking, feature importance.
- Chapter 7, **Dimensionality Reduction** — PCA, compression, explained variance.
- Chapter 8, **Unsupervised Learning Techniques** — k-means, DBSCAN, mixtures, anomaly detection.
- Chapter 9, **Introduction to Artificial Neural Networks** — perceptrons, MLPs, backpropagation concepts.
- Chapter 10, **Building Neural Networks with PyTorch** — tensors, modules, datasets/loaders, training loop, saving/loading.
- Chapter 11, **Training Deep Neural Networks** — initialization, normalization, optimizers, scheduling, regularization, transfer learning.
- Appendix A, **Autodiff** — especially reverse-mode autodiff.
- Appendix B, **Mixed Precision and Quantization** — number formats, post-training quantization, QAT, quantized LLM concepts.

### Optional only if ahead

- Chapter 15 for transformer/LLM grounding.
- Chapter 17 for transformer inference speedups.
- Do not let advanced architectures displace the required classical ML/evaluation path.

### Completion test

From a blank file, use NumPy to implement and explain linear regression, logistic regression, gradient descent, k-means, and PCA at a small educational scale. With scikit-learn/PyTorch, build an end-to-end train/evaluate/save/load/predict path. Explain data leakage, bias/variance, regularization, calibration vs. discrimination, batch size, precision, quantization, throughput vs. latency, and training-serving skew. The `small_projects/inference_service/` baseline must expose a model behind a tested request schema and collect latency/error measurements.

## 4. Summer 2027 — protocol/blockchain literacy

**Exact title:** *Mastering Bitcoin: Programming the Open Blockchain, Third Edition*  
**Authors:** Andreas M. Antonopoulos and David A. Harding  
**ISBN:** 9781098150082

### Required path

- Chapters 2–4 — transaction flow, Bitcoin Core, keys and addresses.
- Chapters 6–9 — transaction serialization, script authorization, ECDSA/Schnorr signatures, fees and fee bumping.
- Chapters 10–12 — peer-to-peer network, mempools, blocks/Merkle trees, proof of work, validation, forks and consensus changes.
- Chapter 13 — threat models and secure system design.
- Chapter 14 — payment/state channels and Lightning concepts.
- Appendix A — read the whitepaper after the modern protocol chapters, then note what the modern system changed or clarified.

### Skip or skim

- Skim Chapter 1; do not spend study time buying coins or comparing wallets.
- Chapter 5 is optional detail unless wallet engineering becomes a target role.
- Use regtest/testnet only. Do not use real funds for coursework.

### Completion test

Explain UTXOs, transaction serialization, signatures, scripts, fee markets, mempool behavior, block validation, Merkle proofs, proof of work, reorgs, soft vs. hard forks, and payment channels. Build one small parser/inspector—Python first, then a Rust rewrite if time—and test it against fixed public fixtures. Be able to state which guarantees come from cryptography, consensus, networking, or local policy.

## How to read any active book

For each assigned section:

1. Preview headings and write two questions.
2. Read with the code closed.
3. Reproduce one example or draw the mechanism from memory.
4. Write a five-sentence explanation and one failure case.
5. Do one representative exercise.
6. Mark it complete only after a 24-hour no-notes explanation.

No highlights-only completion and no passive marathon reading.
