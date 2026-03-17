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

**TEAMMATE PROMPT:**
"I am working on the Smart-IV project with Hrishi. I have checked out the `akash-dev` branch. Please read the project context from `.gemini/antigravity/project_state.md` and follow the collaboration guidelines in `.gemini/antigravity/COLLABORATION.md`. From now on, whenever I ask to sync, use the `.gemini/antigravity/scripts/sync.ps1` script to keep our project states aligned."

---

## 3. How to Sync
Whenever you finish a session or want to see Hrishi's updates:
1. Tell Antigravity: "Run sync" 
   *(This will pull updates, add your changes, and push to akash-dev)*.
2. Periodically merge `main` into your branch to stay updated with project-wide changes.
