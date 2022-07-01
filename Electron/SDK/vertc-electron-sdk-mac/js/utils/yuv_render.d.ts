/// <reference types="node" />
interface YUVFrame {
    format: {
        width: number;
        height: number;
        rotation: number;
        chromaWidth: number;
        chromaHeight: number;
        cropLeft: number;
        cropTop: number;
        cropWidth: number;
        cropHeight: number;
        displayWidth: number;
        displayHeight: number;
    };
    y: {
        bytes: Buffer;
        stride: number;
    };
    u: {
        bytes: Buffer;
        stride: number;
    };
    v: {
        bytes: Buffer;
        stride: number;
    };
}
export declare class YUVRender {
    context_: any;
    parent: HTMLDivElement;
    container: HTMLDivElement;
    canvas: HTMLCanvasElement;
    renderMode: number;
    yuvCanvas: any;
    destroied: boolean;
    mirror_: boolean;
    static buildYUVFrame(data: any): YUVFrame;
    constructor(element: HTMLDivElement, renderMode: number | undefined, mirror: boolean, context: any);
    destroy(): void;
    setMirrorType(mirror: boolean): void;
    clearFrame(): void;
    renderFrame(frame: YUVFrame): void;
    adjustRender(frame: YUVFrame): void;
}
export {};
