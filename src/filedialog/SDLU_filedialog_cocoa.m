#ifdef FILEDIALOG_COCOA

#import <Cocoa/Cocoa.h>
#include "SDLU.h"
#include "SDLU_common.h"
#include <wchar.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x);

static const char*
COCOA_OpenFileDialog(const char* title)
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    const char* filename = NULL;
    NSOpenPanel * panel = [NSOpenPanel openPanel];

    panel.title = [NSString stringWithUTF8String : title];
    panel.canChooseFiles = YES;
    panel.canChooseDirectories = NO;
    panel.allowsMultipleSelection = NO;

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = SDL_strdup([[[panel URL] path] UTF8String]);
    }

    [pool release];
    return filename;
}

static const char*
COCOA_SaveFileDialog(const char* title)
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    const char* filename = NULL;
    NSSavePanel* panel = [NSSavePanel savePanel];

    panel.canCreateDirectories = YES;
    panel.title = [NSString stringWithUTF8String : title];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = SDL_strdup([[[panel URL] path] UTF8String]);
    }

    [pool release];
    return filename;
}

static const char*
COCOA_FolderFileDialog(const char* title)
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    const char* filename = NULL;
    NSOpenPanel * panel = [NSOpenPanel openPanel];

    panel.title = [NSString stringWithUTF8String : title];
    panel.canChooseFiles = NO;
    panel.canChooseDirectories = YES;
    panel.allowsMultipleSelection = NO;

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = SDL_strdup([[[panel URL] path] UTF8String]);
    }

    [pool release];
    return filename;
}

const char*
COCOA_FileDialog(const char* title, Uint32 mode)
{
    if (!mode) mode = SDLU_FILEDIALOG_OPEN;

    if (mode & SDLU_FILEDIALOG_OPEN) {
        return COCOA_OpenFileDialog(title);
    } else if (mode & SDLU_FILEDIALOG_SAVE) {
        return COCOA_SaveFileDialog(title);
    } else if (mode & SDLU_FILEDIALOG_OPENDIR) {
        return COCOA_FolderFileDialog(title);
    } else {
        SDLU_ExitError("Unknown file dialog mode", NULL);
    }
}

void
COCOA_FreeFileDialogFilename(char* filename)
{
    if (filename) SDL_free(filename);
}

static const wchar_t*
COCOA_OpenFileDialogW(const wchar_t* title)
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    const wchar_t* filename = NULL;
    NSOpenPanel * panel = [NSOpenPanel openPanel];

    panel.canChooseFiles = YES;
    panel.canChooseDirectories = NO;
    panel.allowsMultipleSelection = NO;
    panel.title = [[NSString alloc] initWithBytes: title length: SDL_wcslen(title) * sizeof(wchar_t) encoding: NSUTF32LittleEndianStringEncoding];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = wcsdup((wchar_t*)[[[panel URL] path] cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
    }

    [pool release];
    return filename;
}

static const wchar_t*
COCOA_SaveFileDialogW(const wchar_t* title)
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    const wchar_t* filename = NULL;
    NSSavePanel* panel = [NSSavePanel savePanel];

    panel.title = [[NSString alloc] initWithBytes:title length:SDL_wcslen(title) * sizeof(wchar_t) encoding:NSUTF32LittleEndianStringEncoding];
    panel.canCreateDirectories = YES;

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = wcsdup((wchar_t*)[[[panel URL] path] cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
    }

    [pool release];
    return filename;
}

static const wchar_t*
COCOA_FolderFileDialogW(const wchar_t* title)
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    const wchar_t* filename = NULL;
    NSOpenPanel * panel = [NSOpenPanel openPanel];

    panel.canChooseFiles = NO;
    panel.canChooseDirectories = YES;
    panel.allowsMultipleSelection = NO;
    panel.title = [[NSString alloc] initWithBytes:title length:SDL_wcslen(title) * sizeof(*title) encoding:NSUTF32LittleEndianStringEncoding];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = wcsdup((wchar_t*)[[[panel URL] path] cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
    }

    [pool release];
    return filename;
}

const wchar_t*
COCOA_FileDialogW(const wchar_t* title, Uint32 mode)
{
    if (!mode) mode = SDLU_FILEDIALOG_OPEN;

    if (mode & SDLU_FILEDIALOG_OPEN) {
        return COCOA_OpenFileDialogW(title);
    } else if (mode & SDLU_FILEDIALOG_SAVE) {
        return COCOA_SaveFileDialogW(title);
    } else if (mode & SDLU_FILEDIALOG_OPENDIR) {
        return COCOA_FolderFileDialogW(title);
    } else {
        SDLU_ExitError("Unknown file dialog mode", NULL);
    }
}

void
COCOA_FreeFileDialogFilenameW(wchar_t* filename)
{
    if (filename) free(filename);
}

#endif /* FILEDIALOG_COCOA */
