#pragma once

#include <tiffio.hxx>
#include <cstring>

void createImage(const int width, const int height, const int spp, const char *imgData) {

        TIFF* tif = TIFFOpen("test.tif", "w");

        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, spp);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

        tsize_t linebytes = spp * width;

        unsigned char *buf = NULL;

        if(TIFFScanlineSize(tif) >= linebytes) 
                buf = (unsigned char *)_TIFFmalloc(linebytes);
        else
                buf = (unsigned char *)_TIFFmalloc(TIFFScanlineSize(tif));

        TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif, width * spp));

        for(uint32_t row = 0; row < height; row++) {

                memcpy(buf, &imgData[(height - row - 1) * linebytes], linebytes);
                if(TIFFWriteScanline(tif, buf, row, 0) < 0) break;
                std::cout << "\rScanlines remaining: " << height - row << std::flush;
        }

        std::cout << "\nDone\n";

        (void)TIFFClose(tif);

        if(buf) _TIFFfree(buf);
}