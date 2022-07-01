"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const YUVCanvas = require('yuv-canvas');
const { RenderMode } = require("../types");
class YUVRender {
    constructor(element, renderMode = RenderMode.FIT, mirror, context) {
        this.destroied = false;
        // [parentDiv [containerDiv [canvas ]]];
        this.parent = element;
        this.renderMode = renderMode;
        this.container = document.createElement('div');
        this.mirror_ = mirror;
        this.context_ = context || {};
        // this.container.style.border = '1px solid red'; // for debug
        Object.assign(this.container.style, {
            width: '100%',
            height: '100%',
            display: 'flex',
            justifyContent: 'center',
            alignItems: 'center',
            backgroundColor: "black"
        });
        this.canvas = document.createElement('canvas');
        this.canvas.setAttribute("style", "overflow: hidden");
        this.parent.appendChild(this.container);
        this.container.appendChild(this.canvas);
        // by my test results, it will cose averate 12ms to render a YUV frame if webGL is off
        // and it will cost about 3ms whe webGL is on
        let flagUseWebGLRenderer = true;
        if (this.context_.flagUseWebGLRenderer) {
            flagUseWebGLRenderer = true;
        }
        this.yuvCanvas = YUVCanvas.attach(this.canvas, { webGL: flagUseWebGLRenderer });
    }
    // see https://github.com/brion/yuv-buffer
    static buildYUVFrame(data) {
        const { format, width, height, planeY, planeU, planeV, planeSizeY, planeSizeU, planeSizeV, rotation, displayWidth, displayHeight } = data;
        let frame = {
            format: {
                width: width,
                height: height,
                chromaWidth: width / 2,
                chromaHeight: height / 2,
                cropLeft: 0,
                cropTop: 0,
                cropWidth: width,
                cropHeight: height,
                displayWidth: width,
                displayHeight: height,
                rotation: rotation,
            },
            y: { bytes: planeY, stride: planeSizeY },
            u: { bytes: planeU, stride: planeSizeU },
            v: { bytes: planeV, stride: planeSizeV }
        };
        return frame;
    }
    destroy() {
        if (!this.destroied) {
            this.yuvCanvas.clear();
            this.canvas.remove();
            this.container.remove();
            this.yuvCanvas = null;
            this.destroied = true;
        }
    }
    setMirrorType(mirror) {
        this.mirror_ = mirror;
    }
    clearFrame() {
        if (this.yuvCanvas) {
            this.yuvCanvas.clear();
        }
        else {
            console.warn('call renderFrame, but yuvCanvas is null');
        }
    }
    renderFrame(frame) {
        if (this.yuvCanvas) {
            this.adjustRender(frame);
            if (this.context_.flagNotRenderFrame) {
            }
            else {
                this.yuvCanvas.drawFrame(frame);
            }
        }
        else {
            console.warn('call renderFrame, but yuvCanvas is null');
        }
    }
    adjustRender(frame) {
        let containerRatio = this.container.clientWidth / this.container.clientHeight;
        let targetWidth;
        let targetHeight;
        if (frame.format.rotation === 90 || frame.format.rotation === 270) {
            targetWidth = frame.format.height;
            targetHeight = frame.format.width;
        }
        else {
            targetWidth = frame.format.width;
            targetHeight = frame.format.height;
        }
        let frameRatio = targetWidth / targetHeight;
        switch (this.renderMode) {
            case RenderMode.HIDDEN:
                {
                    if (containerRatio >= frameRatio) {
                        this.canvas.style.zoom = String(this.container.clientWidth / targetWidth);
                    }
                    else {
                        this.canvas.style.zoom = String(this.container.clientHeight / targetHeight);
                    }
                    let transform = 'rotateZ(' + frame.format.rotation.toString() + 'deg)';
                    if (this.mirror_) {
                        transform += ' rotateY(180deg)';
                    }
                    this.canvas.style.transform = transform;
                }
                break;
            case RenderMode.FIT:
                {
                    if (containerRatio >= frameRatio) {
                        this.canvas.style.zoom = String(this.container.clientHeight / targetHeight);
                    }
                    else {
                        this.canvas.style.zoom = String(this.container.clientWidth / targetWidth);
                    }
                    let transform = 'rotateZ(' + frame.format.rotation.toString() + 'deg)';
                    if (this.mirror_) {
                        transform += ' rotateY(180deg)';
                    }
                    this.canvas.style.transform = transform;
                }
                break;
            default:
                {
                    console.warn(`adjustRender with an unexpected mode: ${this.renderMode}`);
                }
                break;
        }
    }
}
exports.YUVRender = YUVRender;
//# sourceMappingURL=yuv_render.js.map