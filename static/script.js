fetch('https://api.github.com/repos/Dolaxom/cpp_victory')
    .then(response => response.json())
    .then(data => {
        document.getElementById('stargazers_count').textContent = data.stargazers_count;
    })
    .catch(error => console.error('Error from GitHub API, error =', error));

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

updateYears();
setInterval(updateYears, 100);