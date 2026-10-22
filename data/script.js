const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const fileInput = document.getElementById("fileInput");
const modo = document.getElementById("modo");
const rotacion = document.getElementById("rotacion");
const posX = document.getElementById("posX");
const posY = document.getElementById("posY");
const reset = document.getElementById("reset");
const autoVertical = document.getElementById("autoVertical");

const ANCHO = 128;
const ALTO = 160;

let imagen = new Image();
let imagenCargada = false;

// Mostrar las barras de posición solo en modo recorte
function actualizarControles() {
    const mostrar = modo.value === "crop";

    posX.style.display = mostrar ? "block" : "none";
    posY.style.display = mostrar ? "block" : "none";

    posX.previousElementSibling.style.display = mostrar ? "block" : "none";
    posY.previousElementSibling.style.display = mostrar ? "block" : "none";
}

// Calcular dimensiones de la imagen después del escalado
function obtenerDimensiones() {
    const angulo = Number(rotacion.value);
    const rotadaHorizontal = angulo === 90 || angulo === 270;

    const anchoOriginal = rotadaHorizontal ? imagen.height : imagen.width;
    const altoOriginal = rotadaHorizontal ? imagen.width : imagen.height;

    let escalaX = ANCHO / anchoOriginal;
    let escalaY = ALTO / altoOriginal;

    if (modo.value === "crop") {
        escalaX = escalaY = Math.max(escalaX, escalaY);
    } else if (modo.value === "contain") {
        escalaX = escalaY = Math.min(escalaX, escalaY);
    }

    return {
        ancho: anchoOriginal * escalaX,
        alto: altoOriginal * escalaY
    };
}

// Dibujar imagen en el canvas
function dibujarImagen() {
    ctx.clearRect(0, 0, ANCHO, ALTO);

    if (!imagenCargada) {
        ctx.fillStyle = "#eeeeee";
        ctx.fillRect(0, 0, ANCHO, ALTO);
        return;
    }

    const anguloGrados = Number(rotacion.value);
    const angulo = anguloGrados * Math.PI / 180;

    const dimensiones = obtenerDimensiones();
    const anchoDibujo = dimensiones.ancho;
    const altoDibujo = dimensiones.alto;

    let desplazamientoX = Number(posX.value) * ANCHO / 100;
    let desplazamientoY = Number(posY.value) * ALTO / 100;

    // Limitar movimiento para evitar espacios vacíos
    if (modo.value === "crop") {
        const maxX = Math.max(0, (anchoDibujo - ANCHO) / 2);
        const maxY = Math.max(0, (altoDibujo - ALTO) / 2);

        desplazamientoX = Math.max(
            -maxX,
            Math.min(maxX, desplazamientoX)
        );

        desplazamientoY = Math.max(
            -maxY,
            Math.min(maxY, desplazamientoY)
        );
    }

    ctx.save();

    ctx.beginPath();
    ctx.rect(0, 0, ANCHO, ALTO);
    ctx.clip();

    ctx.translate(
        ANCHO / 2 + desplazamientoX,
        ALTO / 2 + desplazamientoY
    );

    ctx.rotate(angulo);

    if (modo.value === "stretch") {
        ctx.drawImage(
            imagen,
            -ANCHO / 2,
            -ALTO / 2,
            ANCHO,
            ALTO
        );
    } else {
        ctx.drawImage(
            imagen,
            -anchoDibujo / 2,
            -altoDibujo / 2,
            anchoDibujo,
            altoDibujo
        );
    }

    ctx.restore();
}

// Cargar imagen sin rotarla automáticamente
fileInput.addEventListener("change", function () {
    const archivo = this.files[0];

    if (!archivo) return;

    if (!archivo.type.startsWith("image/")) {
        alert("Seleccioná un archivo de imagen válido.");
        return;
    }

    const lector = new FileReader();

    lector.onload = function (evento) {
        imagen.onload = function () {
            imagenCargada = true;

            // Reiniciar posición sin modificar la rotación seleccionada
            posX.value = "0";
            posY.value = "0";

            actualizarControles();
            dibujarImagen();
        };

        imagen.onerror = function () {
            alert("No se pudo cargar la imagen.");
        };

        imagen.src = evento.target.result;
    };

    lector.readAsDataURL(archivo);
});

// Actualizar imagen cuando cambian las opciones
modo.addEventListener("change", function () {
    actualizarControles();
    dibujarImagen();
});

rotacion.addEventListener("change", dibujarImagen);
posX.addEventListener("input", dibujarImagen);
posY.addEventListener("input", dibujarImagen);

// Restablecer los ajustes
reset.addEventListener("click", function () {
    modo.value = "crop";
    rotacion.value = "0";
    posX.value = "0";
    posY.value = "0";

    actualizarControles();
    dibujarImagen();
});

// Generar archivo C en formato RGB565
function generarArchivoC() {
    const imagenData = ctx.getImageData(0, 0, ANCHO, ALTO);
    const pixeles = imagenData.data;

    let contenido = "#include <stdint.h>\n\n";
    contenido += `const uint16_t imagen_plotter[${ANCHO * ALTO}] = {\n`;

    for (let i = 0; i < pixeles.length; i += 4) {
        const r = pixeles[i];
        const g = pixeles[i + 1];
        const b = pixeles[i + 2];

        const rgb565 =
            ((r & 0xF8) << 8) |
            ((g & 0xFC) << 3) |
            (b >> 3);

        contenido += `0x${rgb565.toString(16).padStart(4, "0")},`;

        if (((i / 4) + 1) % 8 === 0) {
            contenido += "\n";
        }
    }

    contenido += "\n};\n";

    const blob = new Blob([contenido], {
        type: "text/plain;charset=utf-8"
    });

    const url = URL.createObjectURL(blob);
    const enlace = document.createElement("a");

    enlace.href = url;
    enlace.download = "imagen_plotter.c";

    document.body.appendChild(enlace);
    enlace.click();
    enlace.remove();

    URL.revokeObjectURL(url);
}

// Botón imprimir
autoVertical.addEventListener("click", function () {
    if (!imagenCargada) {
        alert("Primero tenés que cargar una imagen.");
        return;
    }

    dibujarImagen();
    generarArchivoC();
});

// Inicialización
actualizarControles();
dibujarImagen();