# Project Workflow

## 📑 Table of Contents

- [🏁 Introduction](#-introduction)
- [🚀 Build & Deployment](#-build--deployment)
- [🛠️ Getting Started](#-getting-started)
- [🌿 Branching Strategy](#-branching-strategy)
- [📋 Task Management](#-task-management)
- [👀 Code Review Process](#-code-review-process)
- [📝 Documentation Standards](#-documentation-standards)
- [🛠️ Troubleshooting](#-troubleshooting)
- [❓ Frequently Asked Questions](#-frequently-asked-questions)
- [📬 Contact Information](#-contact-information)

## 🏁 Introduction

Welcome to the Orion Project workflow guide! This document outlines the essential steps and best practices for building, deploying, and collaborating on the project. Use the sections below to navigate through the workflow and ensure a smooth development process.

## 🚀 Build & Deployment

After changes have been made and saved (*Ctrl + S*), when:

### 📝 Updating `sample.cpp` (*Main Code*):
1. Build/Compile the `.cpp` file in VS.
2. Trigger **Live Coding** via *Ctrl + Alt + F11* → Compiles within the UE Editor.

### 📄 Updating `sample.h` (*Header*):
1. Build/Compile the `.h` file in VS.
2. Close then reopen the entire UE Editor → Updates the header in the *Details Panel*.

### ⚠️ To prevent over relaunching Unreal Project:
When creating a new actor class (or any class in that matter):
1. Consider all important headers that work best with the class **BEFORE** initial compilation.

## 🛠️ Getting Started

1. **Clone the Repository**  
    ```sh
    git clone <repo-url>
    cd Orion_Project
    ```

2. **Install Dependencies**  
    - Ensure you have Unreal Engine (recommended version) installed.
    - Install Visual Studio with C++ development tools.

3. **Open the Project**  
    - Launch Unreal Engine.
    - Open the `.uproject` file from the project directory.

4. **Configure Local Settings**  
    - Set up any required environment variables or config files as described in `README.md`.

## 🌿 Branching Strategy

- **Main Branches:**
  - `main`: Production-ready code.
  - `develop`: Latest development changes.

- **Feature Branches:**  
  Create a new branch for each feature or bugfix:
  ```sh
  git checkout develop
  git checkout -b feature/short-description
  ```

- **Pull Requests:**  
  - Open PRs against `develop`.
  - Use clear, descriptive titles and link related issues.

## 📋 Task Management

- Use GitHub Issues or your team's project board.
- Assign tasks with clear descriptions and acceptance criteria.
- Update task status as you progress (To Do → In Progress → Done).

## 👀 Code Review Process

1. Open a pull request with a clear summary.
2. Request at least one reviewer.
3. Address feedback promptly.
4. Merge only after approval and passing checks.

## 📝 Documentation Standards

- Update documentation for any new features or changes.
- Use clear, concise language and code examples where helpful.
- Keep `README.md` and this workflow up to date.

## 🛠️ Troubleshooting

- **Build Fails:**  
  - Check error logs in Visual Studio and UE Editor.
  - Ensure all dependencies are installed.

- **Live Coding Issues:**  
  - Restart UE Editor if changes are not reflected.

- **Common Errors:**  
  - Refer to the [FAQ](#-frequently-asked-questions) section.

## ❓ Frequently Asked Questions

**Q: The editor doesn't recognize my new class.**  
A: Try rebuilding the project and restarting the UE Editor.

**Q: Live Coding isn't working.**  
A: Ensure Live Coding is enabled in UE Editor settings.

**Q: How do I update dependencies?**  
A: Follow the instructions in `README.md`.

## 📬 Contact Information

- **Project Lead:** Gian Alfonso (gianalfonso825@gmail.com or alfonsogian225@gmail.com)
- **Slack/Discord:** lt_noodle
- **Issue Tracker:** Orion Project (https://github.com/Imanoodle13/Orion_Project/issues)
- For urgent issues, mention the team in the appropriate channel.