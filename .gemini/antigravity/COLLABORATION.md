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
"I am working on the Smart-IV project with Hrishi. I have checked out the `akash-dev` branch. Please read the project context from `.gemini/antigravity/project_state.md` and follow the collaboration guidelines in `.gemini/antigravity/COLLABORATION.md`. 

**Automation Rules:**
- Whenever I say 'Sync', run `.gemini/antigravity/scripts/sync.ps1`.
- Automatically generate detailed commit messages based on my work.
- **Integrated Chat**: Always check `.gemini/antigravity/CHAT.md` for new messages from my teammate and alert me.
- Keep my progress synced with the shared state files in the repository."

---

## 3. How Syncing Works
- **No Manual Commits**: Just tell Antigravity "Sync".
- **Descriptive History**: Antigravity will write the commit and merge messages for you.
- **Integrated Chat**: If you want to leave a message for Hrishi, tell Antigravity: "Add to chat: [your message]".
- **Stay in Sync**: Periodically merge `main` into your branch to stay updated with project-wide changes.
