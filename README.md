# Sorting Algorithms Visualizer in C (SDL2, Docker, Jenkins CI)

Interactive sorting algorithm visualizer written in **C** using **SDL2** library, with:
- multiple sorting algorithms (visual + pure, testable)
- automated tests for algorithm correctness
- Docker image for reproducible builds
- Jenkins CI pipeline that builds the Docker image and runs tests periodically

---

## Features

### Visualizer

Implemented sorting algorithms (visualized with SDL2):

- **Bubble Sort**
- **Quick Sort**
- **Inseration Sort**
- **Merge Sort**
- **Heap Sort**

For each algorithm, the app:
- generates a random array
- visualizes the sorting process with colored bars
- displays algorithm name and time/space complexity using a pixel font

## Algorithms: visual vs pure

The project separates **visual** and **pure** implementations of the algorithms:
- `src/sorts.c` - visual versions
- `src/sorts_pure.c` - pure C versions

This separation allows:
- interactive visualization for learning/entertainment purposes
- deterministic, fast tests in CI (no graphics involved)

## Test runner
File: `src/tests.c`

- generates random arrays
- runs each pure sorting algorithm
- verifies the result is sorted

## Build and Run
Tested on Linux Fedora

Prerequisites:
- ```gcc```
- ```make```
- ```SDL2```
- ```SDL2_ttf```

Fedora example:
```sudo dnf install gcc make SDL2-devel SDL2_ttf-devel```

Build:
```make```

This produces:
- ```sorting_visualizer``` - SDL2 GUI application
- ```tests``` - pure C test binary

Run visualizer:
- ```./sorting_visualizer```

From there:
- choose the algorithm in the terminal menu
- watch sorting process animate in the SDL window

Run tests:
- ```./tests```

## How Docker is used in the project
The Dockerfile turns this project into a reproducible CI-friendly unit.
**Key points**:
- Base image: ```debian:stable-slim```
- Installs:
    - build tools(```build-essential```)
    - ```libsdl2-dev```
    - ```libsdl2-ttf-dev```
- Sets ```WORKDIR /app```
- Copies the entire repo into the image:
    - ```COPY . /app```
- Runs:
```RUN make```
```CMD ["./tests"]```

So the image build compiles the visualizer and tests using the project's ```Makefile```, and runs the tests inside the container.

### Local usage
Build image:
```docker build -t sorting-visualizer-ci .```
Run tests in the container:
```docker run --rm sorting-visualizer-ci```

This is exacly what Jenkins does as part of the CI pipeline.

## How Jenkins is used in this project
Jenkins is used (for fun, with a practice purpose) as a **CI automation server** to:
1. Monitor the Git repository for changes
2. Build the Docker image for this project
3. Run the test suite inside the Docker container
4. Mark the pipeline as **SUCCESS** or **FAILURE** based on the tests results.

### Jenkins pipeline
The CI pipeline is defined as code in ```Jenkinsfile```.
What it does:
- Jenkins always uses the same **Dockerfile** and **Makefile** as we do locally
- If the tests fail inside Docker, the Jenkins builds fail too

### Trigger: Poll SCM (not Webhooks here)
I know there are 2 typical ways to trigger Jenkins when code changes:
1. **Webhooks (push-based, ideal for hosted Jenkins)**
The Jenkinsfile in this project can be used this way too, but here, Jenkins runs just locally.
2. **Poll SCM (current setup, for local Jenkins)**
Jenkins is running **locally**, for practicing purposes, and it is not exposed on a public URL.
GitHub cannot directly reach Jenkins for webhooks.
Instead, Jenkins is configured with **Poll SCM**:
- automatically and periodically check the Git repository for new commits
- if there is a new commit, it runs the same pipeline described above, (in the dates of 1, 11 and 21th of every month, basically every ~10 days)
