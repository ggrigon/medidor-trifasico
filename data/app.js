// --- WebSocket ---
let ws;
let chart;
const MAX_POINTS = 300; // 5 min a 1s

function connectWS() {
    const proto = location.protocol === 'https:' ? 'wss:' : 'ws:';
    ws = new WebSocket(proto + '//' + location.host + '/ws');

    ws.onopen = () => {
        document.getElementById('ws-status').textContent = 'Conectado';
        document.getElementById('ws-status').className = 'connected';
    };

    ws.onclose = () => {
        document.getElementById('ws-status').textContent = 'Desconectado';
        document.getElementById('ws-status').className = 'disconnected';
        setTimeout(connectWS, 3000);
    };

    ws.onerror = () => ws.close();

    ws.onmessage = (evt) => {
        try {
            const data = JSON.parse(evt.data);
            if (data.type === 'data') {
                updateUI(data);
                updateChart(data);
            } else if (data.type === 'alarm') {
                showAlarm(data.msg);
            }
        } catch (e) {
            console.error('Erro ao processar dados:', e);
        }
    };
}

function updateUI(data) {
    document.getElementById('timestamp').textContent = data.ts || '';
    document.getElementById('total-power').textContent = formatNumber(data.total_p, 0) + ' W';

    data.phases.forEach((p) => {
        const id = p.id;
        if (p.ok) {
            document.getElementById(id + '-v').textContent = formatNumber(p.v, 1);
            document.getElementById(id + '-i').textContent = formatNumber(p.i, 2);
            document.getElementById(id + '-p').textContent = formatNumber(p.p, 0);
            document.getElementById(id + '-e').textContent = formatNumber(p.e, 3);
            document.getElementById(id + '-f').textContent = formatNumber(p.f, 1);
            document.getElementById(id + '-pf').textContent = formatNumber(p.pf, 2);
            document.getElementById('card-' + id).classList.remove('alarm');
        } else {
            ['v','i','p','e','f','pf'].forEach(k => {
                document.getElementById(id + '-' + k).textContent = '--';
            });
        }
    });
}

function formatNumber(val, decimals) {
    if (val === undefined || val === null) return '--';
    return val.toFixed(decimals);
}

// --- Chart.js ---
function initChart() {
    const ctx = document.getElementById('powerChart').getContext('2d');
    chart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [
                { label: 'L1 (W)', data: [], borderColor: '#e94560', borderWidth: 1.5, pointRadius: 0, fill: false },
                { label: 'L2 (W)', data: [], borderColor: '#5b8fd4', borderWidth: 1.5, pointRadius: 0, fill: false },
                { label: 'L3 (W)', data: [], borderColor: '#53a653', borderWidth: 1.5, pointRadius: 0, fill: false },
                { label: 'Total (W)', data: [], borderColor: '#f5a623', borderWidth: 2, pointRadius: 0, fill: false, borderDash: [5, 3] }
            ]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            animation: { duration: 0 },
            scales: {
                x: {
                    display: true,
                    ticks: { color: '#888', maxTicksLimit: 6, maxRotation: 0 },
                    grid: { color: '#2a2a4a' }
                },
                y: {
                    display: true,
                    ticks: { color: '#888' },
                    grid: { color: '#2a2a4a' },
                    beginAtZero: true
                }
            },
            plugins: {
                legend: {
                    labels: { color: '#ccc', boxWidth: 12, padding: 10 }
                }
            },
            interaction: { intersect: false, mode: 'index' }
        }
    });
}

function updateChart(data) {
    if (!chart) return;

    const time = data.ts ? data.ts.substring(11, 19) : '';
    chart.data.labels.push(time);

    const powers = [0, 0, 0];
    data.phases.forEach((p, i) => {
        powers[i] = p.ok ? p.p : 0;
    });

    chart.data.datasets[0].data.push(powers[0]);
    chart.data.datasets[1].data.push(powers[1]);
    chart.data.datasets[2].data.push(powers[2]);
    chart.data.datasets[3].data.push(data.total_p || 0);

    // Manter apenas ultimos 5 minutos
    if (chart.data.labels.length > MAX_POINTS) {
        chart.data.labels.shift();
        chart.data.datasets.forEach(ds => ds.data.shift());
    }

    chart.update();
}

// --- Alarmes ---
let alarmTimeout;
function showAlarm(msg) {
    const bar = document.getElementById('alarm-bar');
    document.getElementById('alarm-msg').textContent = msg;
    bar.classList.remove('hidden');

    clearTimeout(alarmTimeout);
    alarmTimeout = setTimeout(() => bar.classList.add('hidden'), 15000);
}

// --- Init ---
document.addEventListener('DOMContentLoaded', () => {
    initChart();
    connectWS();
});
