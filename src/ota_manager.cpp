#include "ota_manager.h"
#include <Update.h>

// --- Pagina HTML de update OTA ---
const char* OTAManager::_updatePage = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Atualizar Firmware</title>
<style>
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:'Segoe UI',system-ui,sans-serif;background:#1a1a2e;color:#e0e0e0;min-height:100vh;display:flex;flex-direction:column;align-items:center;padding:40px 20px}
h1{margin-bottom:8px;font-size:1.4rem}
.subtitle{color:#888;margin-bottom:32px;font-size:0.9rem}
.card{background:#16213e;border:1px solid #0f3460;border-radius:12px;padding:32px;max-width:480px;width:100%}
.card h2{font-size:1rem;color:#888;margin-bottom:16px}
.upload-area{border:2px dashed #0f3460;border-radius:8px;padding:32px;text-align:center;cursor:pointer;transition:border-color .2s}
.upload-area:hover,.upload-area.dragover{border-color:#f5a623}
.upload-area input{display:none}
.upload-area .icon{font-size:2rem;margin-bottom:8px}
.upload-area p{color:#888;font-size:0.9rem}
.file-name{color:#f5a623;margin-top:8px;font-size:0.85rem}
#progress-section{display:none;margin-top:20px}
.progress-bar{background:#0f3460;border-radius:6px;height:24px;overflow:hidden;margin:8px 0}
.progress-fill{background:linear-gradient(90deg,#0f3460,#f5a623);height:100%;width:0%;transition:width .3s;border-radius:6px}
.progress-text{text-align:center;font-size:0.85rem;color:#888}
#status-msg{margin-top:16px;padding:12px;border-radius:8px;text-align:center;display:none}
#status-msg.success{display:block;background:#1a3a1a;color:#8f8;border:1px solid #2d6a2d}
#status-msg.error{display:block;background:#3a1a1a;color:#f88;border:1px solid #6a2d2d}
.btn{display:inline-block;padding:10px 24px;background:#f5a623;color:#1a1a2e;border:none;border-radius:6px;font-size:0.95rem;font-weight:600;cursor:pointer;margin-top:16px;text-decoration:none}
.btn:hover{background:#e6951a}
.btn:disabled{background:#555;cursor:not-allowed}
a.back{color:#888;text-decoration:none;margin-top:24px;font-size:0.85rem}
a.back:hover{color:#f5a623}
.info{background:#16213e;border:1px solid #0f3460;border-radius:8px;padding:12px 16px;margin-top:16px;font-size:0.8rem;color:#888}
</style>
</head>
<body>
<h1>Atualizar Firmware</h1>
<p class="subtitle">Medidor Trifasico - OTA Update</p>

<div class="card">
    <h2>Firmware (.bin)</h2>
    <div class="upload-area" id="drop-area" onclick="document.getElementById('file-input').click()">
        <div class="icon">&#128228;</div>
        <p>Clique ou arraste o arquivo .bin aqui</p>
        <input type="file" id="file-input" accept=".bin">
        <div class="file-name" id="file-name"></div>
    </div>

    <div id="progress-section">
        <div class="progress-bar"><div class="progress-fill" id="progress-fill"></div></div>
        <div class="progress-text" id="progress-text">0%</div>
    </div>

    <div id="status-msg"></div>

    <button class="btn" id="upload-btn" onclick="uploadFirmware()" disabled>Atualizar</button>

    <div class="info">
        Apos o upload, o ESP32 reinicia automaticamente com o novo firmware.
        Se algo der errado, o firmware anterior e mantido.
    </div>
</div>

<a href="/" class="back">&larr; Voltar ao dashboard</a>

<script>
const fileInput = document.getElementById('file-input');
const dropArea = document.getElementById('drop-area');
const fileName = document.getElementById('file-name');
const uploadBtn = document.getElementById('upload-btn');
const progressSection = document.getElementById('progress-section');
const progressFill = document.getElementById('progress-fill');
const progressText = document.getElementById('progress-text');
const statusMsg = document.getElementById('status-msg');

let selectedFile = null;

fileInput.addEventListener('change', (e) => {
    selectFile(e.target.files[0]);
});

['dragenter','dragover'].forEach(ev => {
    dropArea.addEventListener(ev, (e) => { e.preventDefault(); dropArea.classList.add('dragover'); });
});
['dragleave','drop'].forEach(ev => {
    dropArea.addEventListener(ev, (e) => { e.preventDefault(); dropArea.classList.remove('dragover'); });
});
dropArea.addEventListener('drop', (e) => {
    selectFile(e.dataTransfer.files[0]);
});

function selectFile(file) {
    if (!file) return;
    if (!file.name.endsWith('.bin')) {
        showStatus('Selecione um arquivo .bin', 'error');
        return;
    }
    selectedFile = file;
    fileName.textContent = file.name + ' (' + (file.size / 1024).toFixed(0) + ' KB)';
    uploadBtn.disabled = false;
    statusMsg.style.display = 'none';
}

function uploadFirmware() {
    if (!selectedFile) return;

    const xhr = new XMLHttpRequest();
    const formData = new FormData();
    formData.append('firmware', selectedFile);

    xhr.open('POST', '/update');

    xhr.upload.addEventListener('progress', (e) => {
        if (e.lengthComputable) {
            const pct = Math.round((e.loaded / e.total) * 100);
            progressFill.style.width = pct + '%';
            progressText.textContent = pct + '%';
        }
    });

    xhr.onload = () => {
        if (xhr.status === 200) {
            showStatus('Firmware atualizado! Reiniciando em 3s...', 'success');
            uploadBtn.disabled = true;
            setTimeout(() => { location.href = '/'; }, 5000);
        } else {
            showStatus('Erro: ' + xhr.responseText, 'error');
            uploadBtn.disabled = false;
        }
    };

    xhr.onerror = () => {
        showStatus('Erro de conexao. O ESP32 pode estar reiniciando.', 'error');
        setTimeout(() => { location.href = '/'; }, 5000);
    };

    progressSection.style.display = 'block';
    uploadBtn.disabled = true;
    statusMsg.style.display = 'none';
    xhr.send(formData);
}

function showStatus(msg, type) {
    statusMsg.textContent = msg;
    statusMsg.className = type;
}
</script>
</body>
</html>
)rawliteral";

// --- ArduinoOTA (upload via terminal/PlatformIO) ---
void OTAManager::begin(const String& hostname) {
    ArduinoOTA.setHostname(hostname.c_str());

    ArduinoOTA.onStart([]() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "firmware" : "filesystem";
        Serial.println("[OTA] Iniciando update: " + type);
    });

    ArduinoOTA.onEnd([]() {
        Serial.println("\n[OTA] Update concluido!");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("[OTA] Progresso: %u%%\r", (progress * 100) / total);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("[OTA] Erro[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth falhou");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin falhou");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect falhou");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive falhou");
        else if (error == OTA_END_ERROR) Serial.println("End falhou");
    });

    ArduinoOTA.begin();
    Serial.printf("[OTA] ArduinoOTA pronto - hostname: %s\n", hostname.c_str());
}

void OTAManager::loop() {
    ArduinoOTA.handle();
}

// --- Web OTA (upload via navegador) ---
void OTAManager::setupWebOTA(AsyncWebServer* server) {
    // Pagina de upload
    server->on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/html", _updatePage);
    });

    // Receber firmware
    server->on("/update", HTTP_POST,
        // Callback de conclusao
        [](AsyncWebServerRequest* request) {
            bool success = !Update.hasError();
            AsyncWebServerResponse* response = request->beginResponse(
                success ? 200 : 500,
                "text/plain",
                success ? "OK" : "FALHA no update"
            );
            response->addHeader("Connection", "close");
            request->send(response);
            if (success) {
                Serial.println("[OTA-WEB] Update OK, reiniciando...");
                delay(1000);
                ESP.restart();
            }
        },
        // Callback de upload (chamado por chunk)
        [](AsyncWebServerRequest* request, const String& filename,
           size_t index, uint8_t* data, size_t len, bool final) {

            if (index == 0) {
                Serial.printf("[OTA-WEB] Recebendo: %s\n", filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
                    Update.printError(Serial);
                }
            }

            if (Update.isRunning()) {
                if (Update.write(data, len) != len) {
                    Update.printError(Serial);
                }
            }

            if (final) {
                if (Update.end(true)) {
                    Serial.printf("[OTA-WEB] Upload completo: %u bytes\n", index + len);
                } else {
                    Update.printError(Serial);
                }
            }
        }
    );

    Serial.println("[OTA-WEB] Pagina de update em /update");
}
