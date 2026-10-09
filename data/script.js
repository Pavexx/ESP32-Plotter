

"use strict";

// ============================================================
// CONFIGURACIÓN
// ============================================================

const WIDTH = 128;
const HEIGHT = 160;

// ============================================================
// ELEMENTOS HTML
// ============================================================

const fileInput = document.getElementById("fileInput");

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const modo = document.getElementById("modo");
const rotacion = document.getElementById("rotacion");

const posX = document.getElementById("posX");
const posY = document.getElementById("posY");

const posXValue = document.getElementById("posXValue");
const posYValue = document.getElementById("posYValue");

const infoOriginal = document.getElementById("infoOriginal");
const infoFinal = document.getElementById("infoFinal");
const tamano = document.getElementById("tamano");

const actualizar = document.getElementById("actualizar");
const descargar = document.getElementById("descargar");
const descargarBinario = document.getElementById("descargarBinario");

const autoVertical = document.getElementById("autoVertical");
const reset = document.getElementById("reset");

// ============================================================
// VARIABLES
// ============================================================

let imagen = null;
let nombreOriginal = "imagen";

let datosRGB565 = null;
let contenidoC = "";


// ============================================================
// CARGAR IMAGEN
// ============================================================

fileInput.addEventListener("change", function () {

    const file = this.files[0];

    if (!file) {
        return;
    }

    nombreOriginal = file.name
        .replace(/\.[^/.]+$/, "")
        .replace(/[^a-zA-Z0-9_]/g, "_");

    const url = URL.createObjectURL(file);

    const img = new Image();

    img.onload = function () {

        imagen = img;

        infoOriginal.textContent =
            img.width +
            " × " +
            img.height +
            " píxeles";

        // Si es horizontal, sugerir rotación vertical
        if (img.width > img.height) {
            rotacion.value = "90";
        } else {
            rotacion.value = "0";
        }

        actualizarImagen();

        URL.revokeObjectURL(url);
    };

    img.onerror = function () {
        alert("No se pudo cargar la imagen.");
    };

    img.src = url;
});


// ============================================================
// ACTUALIZAR VISTA
// ============================================================

function actualizarImagen() {

    if (!imagen) {
        return;
    }

    ctx.clearRect(0, 0, WIDTH, HEIGHT);

    // Fondo negro
    ctx.fillStyle = "#000000";
    ctx.fillRect(0, 0, WIDTH, HEIGHT);

    const grados = parseInt(rotacion.value);

    const radianes = grados * Math.PI / 180;

    const modoActual = modo.value;

    // --------------------------------------------------------
    // Calcular dimensiones después de rotar
    // --------------------------------------------------------

    let srcW = imagen.width;
    let srcH = imagen.height;

    if (grados === 90 || grados === 270) {
        srcW = imagen.height;
        srcH = imagen.width;
    }

    // --------------------------------------------------------
    // STRETCH
    // --------------------------------------------------------

    if (modoActual === "stretch") {

        ctx.save();

        ctx.translate(WIDTH / 2, HEIGHT / 2);
        ctx.rotate(radianes);

        ctx.drawImage(
            imagen,
            -imagen.width / 2,
            -imagen.height / 2,
            imagen.width,
            imagen.height
        );

        ctx.restore();

        // En stretch realmente queremos ocupar todo el canvas.
        // Volvemos a dibujar usando un canvas temporal.

        const temporal = document.createElement("canvas");

        temporal.width = srcW;
        temporal.height = srcH;

        const tctx = temporal.getContext("2d");

        tctx.save();

        tctx.translate(srcW / 2, srcH / 2);
        tctx.rotate(radianes);

        tctx.drawImage(
            imagen,
            -imagen.width / 2,
            -imagen.height / 2
        );

        tctx.restore();

        ctx.clearRect(0, 0, WIDTH, HEIGHT);

        ctx.drawImage(
            temporal,
            0,
            0,
            srcW,
            srcH,
            0,
            0,
            WIDTH,
            HEIGHT
        );

    }

    // --------------------------------------------------------
    // CONTAIN / CROP
    // --------------------------------------------------------

    else {

        const escalaX = WIDTH / srcW;
        const escalaY = HEIGHT / srcH;

        let escala;

        if (modoActual === "crop") {
            escala = Math.max(escalaX, escalaY);
        } else {
            escala = Math.min(escalaX, escalaY);
        }

        const dstW = srcW * escala;
        const dstH = srcH * escala;

        const desplazamientoX =
            (WIDTH - dstW) / 2 +
            parseInt(posX.value);

        const desplazamientoY =
            (HEIGHT - dstH) / 2 +
            parseInt(posY.value);

        // Canvas temporal para realizar la rotación
        const temporal = document.createElement("canvas");

        temporal.width = srcW;
        temporal.height = srcH;

        const tctx = temporal.getContext("2d");

        tctx.save();

        tctx.translate(srcW / 2, srcH / 2);
        tctx.rotate(radianes);

        tctx.drawImage(
            imagen,
            -imagen.width / 2,
            -imagen.height / 2
        );

        tctx.restore();

        ctx.drawImage(
            temporal,
            0,
            0,
            srcW,
            srcH,
            desplazamientoX,
            desplazamientoY,
            dstW,
            dstH
        );
    }

    // --------------------------------------------------------
    // Generar RGB565
    // --------------------------------------------------------

    generarRGB565();

    // --------------------------------------------------------
    // Información
    // --------------------------------------------------------

    infoFinal.innerHTML =
        "Imagen convertida a <strong>" +
        WIDTH +
        " × " +
        HEIGHT +
        "</strong> píxeles.<br>" +
        "Formato: <strong>RGB565</strong><br>" +
        "Bytes: <strong>" +
        datosRGB565.length +
        "</strong>";

    tamano.textContent =
        datosRGB565.length + " bytes";
}


// ============================================================
// RGB888 -> RGB565
// ============================================================

function convertirRGB565(r, g, b) {

    return (
        ((r & 0xF8) << 8) |
        ((g & 0xFC) << 3) |
        (b >> 3)
    );
}


// ============================================================
// GENERAR DATOS RGB565
// ============================================================

function generarRGB565() {

    const imageData =
        ctx.getImageData(
            0,
            0,
            WIDTH,
            HEIGHT
        );

    const pixels = imageData.data;

    datosRGB565 =
        new Uint8Array(
            WIDTH * HEIGHT * 2
        );

    let offset = 0;

    for (let i = 0; i < pixels.length; i += 4) {

        const r = pixels[i];
        const g = pixels[i + 1];
        const b = pixels[i + 2];

        const color =
            convertirRGB565(r, g, b);

        // ----------------------------------------------------
        // IMPORTANTE:
        //
        // Little endian.
        //
        // Esto coincide con el true que usamos en:
        //
        // tft.pushColors(..., true);
        // ----------------------------------------------------

        datosRGB565[offset++] =
            color & 0xFF;

        datosRGB565[offset++] =
            (color >> 8) & 0xFF;
    }

    generarC();
}


// ============================================================
// GENERAR ARCHIVO .C
// ============================================================

function generarC() {

    if (!datosRGB565) {
        return;
    }

    let texto = "";

    texto +=
        "#include <stdint.h>\n";

    texto +=
        "#include <lvgl.h>\n\n";

    texto +=
        "// =====================================================\n";

    texto +=
        "// Imagen LVGL\n";

    texto +=
        "// Resolucion: 128 x 160\n";

    texto +=
        "// Formato: RGB565\n";

    texto +=
        "// =====================================================\n\n";

    texto +=
        "const uint8_t imagen_data[] = {\n";

    for (let i = 0; i < datosRGB565.length; i++) {

        if (i % 16 === 0) {
            texto += "    ";
        }

        texto +=
            "0x" +
            datosRGB565[i]
                .toString(16)
                .padStart(2, "0")
                .toUpperCase();

        if (i < datosRGB565.length - 1) {
            texto += ", ";
        }

        if (i % 16 === 15) {
            texto += "\n";
        }
    }

    if (datosRGB565.length % 16 !== 0) {
        texto += "\n";
    }

    texto +=
        "};\n\n";

    texto +=
        "// Descriptor LVGL\n";

    texto +=
        "const lv_image_dsc_t imagen = {\n";

    texto +=
        "    .header.magic = LV_IMAGE_HEADER_MAGIC,\n";

    texto +=
        "    .header.cf = LV_COLOR_FORMAT_RGB565,\n";

    texto +=
        "    .header.w = 128,\n";

    texto +=
        "    .header.h = 160,\n";

    texto +=
        "    .data_size = sizeof(imagen_data),\n";

    texto +=
        "    .data = imagen_data\n";

    texto +=
        "};\n";

    contenidoC = texto;
}


// ============================================================
// DESCARGAR .C
// ============================================================

descargar.addEventListener("click", function () {

    if (!datosRGB565) {
        alert("Primero selecciona una imagen.");
        return;
    }

    const blob =
        new Blob(
            [contenidoC],
            {
                type: "text/plain;charset=utf-8"
            }
        );

    const url =
        URL.createObjectURL(blob);

    const a =
        document.createElement("a");

    a.href = url;

    a.download =
        "imagen_lvgl.c";

    document.body.appendChild(a);

    a.click();

    document.body.removeChild(a);

    URL.revokeObjectURL(url);
});
enviarESP32.addEventListener(
    "click",
    async function () {

        if (!datosRGB565) {
            alert(
                "Primero selecciona una imagen."
            );

            return;
        }


        estadoESP32.textContent =
            "Enviando imagen...";


        try {

            const formData =
                new FormData();


            const blob =
                new Blob(
                    [datosRGB565],
                    {
                        type:
                            "application/octet-stream"
                    }
                );


            formData.append(
                "imagen",
                blob,
                "imagen.rgb565"
            );


            const respuesta =
                await fetch(
                    "/upload",
                    {
                        method: "POST",
                        body: formData
                    }
                );


            if (!respuesta.ok) {
                throw new Error(
                    "HTTP " +
                    respuesta.status
                );
            }


            estadoESP32.textContent =
                "✓ Imagen mostrada en el ESP32";


        }
        catch (error) {

            console.error(error);

            estadoESP32.textContent =
                "✗ Error enviando imagen";
        }
    }
);


// ============================================================
// DESCARGAR BINARIO
// ============================================================

descargarBinario.addEventListener(
    "click",
    function () {

        if (!datosRGB565) {
            alert("Primero selecciona una imagen.");
            return;
        }

        const blob =
            new Blob(
                [datosRGB565],
                {
                    type: "application/octet-stream"
                }
            );

        const url =
            URL.createObjectURL(blob);

        const a =
            document.createElement("a");

        a.href = url;

        a.download =
            "imagen_rgb565.bin";

        document.body.appendChild(a);

        a.click();

        document.body.removeChild(a);

        URL.revokeObjectURL(url);
    }
);


// ============================================================
// BOTÓN ACTUALIZAR
// ============================================================

actualizar.addEventListener(
    "click",
    function () {

        actualizarImagen();
    }
);


// ============================================================
// CAMBIOS AUTOMÁTICOS
// ============================================================

modo.addEventListener(
    "change",
    actualizarImagen
);

rotacion.addEventListener(
    "change",
    actualizarImagen
);

posX.addEventListener(
    "input",
    function () {

        posXValue.textContent =
            posX.value;

        actualizarImagen();
    }
);

posY.addEventListener(
    "input",
    function () {

        posYValue.textContent =
            posY.value;

        actualizarImagen();
    }
);


// ============================================================
// ROTACIÓN AUTOMÁTICA
// ============================================================

autoVertical.addEventListener(
    "click",
    function () {

        if (!imagen) {
            alert("Primero selecciona una imagen.");
            return;
        }

        if (imagen.width > imagen.height) {
            rotacion.value = "90";
        } else {
            rotacion.value = "0";
        }

        actualizarImagen();
    }
);


// ============================================================
// RESTABLECER
// ============================================================

reset.addEventListener(
    "click",
    function () {

        modo.value = "crop";

        rotacion.value = "0";

        posX.value = "0";
        posY.value = "0";

        posXValue.textContent = "0";
        posYValue.textContent = "0";

        actualizarImagen();
    }
);

