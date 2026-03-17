# Antigravity Collaboration Guide (For Akash)

Welcome to the **Smart-IV** project! To ensure our Antigravity instances are in sync, follow these steps.

## 1. Setup Your Workspace
1. Clone the repository if you haven't already.
2. Run the following command in your terminal:
   ```powershell
   git checkout akash-dev
   ```

## 2. Onboard Antigravity
Copy and paste the following prompt into your Antigravity chat:

---

**Automation Rules:**
- Whenever I say 'Sync', run `.gemini/antigravity/scripts/sync.ps1`.
- Automatically generate detailed commit messages based on my work.
- Keep my progress synced with the shared state files in the repository."

---

## 3. How Syncing Works
- **No Manual Commits**: Just tell Antigravity "Sync".
- **Descriptive History**: Antigravity will write the commit and merge messages for you.
- **Stay in Sync**: Periodically merge `main` into your branch to stay updated with project-wide changes.
