// GitHub start

async function fetchGitHubStars() {
    try {
        const response = await fetch("https://api.github.com/repos/Dolaxom/cpp_victory");

        if (!response.ok) {
            throw new Error(`GitHub API error: ${response.status}`);
        }

        const data = await response.json();
        document.getElementById('github-stars').textContent = data.stargazers_count || 0;
    } catch (error) {
        console.error('Error fetching data from GitHub:', error);
        document.getElementById('github-stars').textContent = "Error";
    }
}

fetchGitHubStars();

// Real-time years counter

const startYear = 1985;
const yearsSince1985 = () => {
    const now = new Date();
    const start = new Date(startYear, 0, 1);
    const diff = now - start;
    const years = diff / (1000 * 60 * 60 * 24 * 365.25);
    return years.toFixed(16);
};

const updateYears = () => {
    document.getElementById('years-since-1985').textContent = yearsSince1985();
};

// Likes

async function updateLikeCount() {
    try {
        const res = await fetch("/like");
        const data = await res.json();
        document.getElementById("like-count").textContent = data.like;
    } catch (e) {
        console.error("Не удалось получить количество лайков:", e);
    }
}

document.getElementById("like-button").addEventListener("click", async () => {
    try {
        await fetch("/like", { method: "POST" });
        updateLikeCount();
    } catch (e) {
        console.error("Ошибка при отправке лайка:", e);
    }
});

updateLikeCount();

updateYears();
setInterval(updateYears, 100);