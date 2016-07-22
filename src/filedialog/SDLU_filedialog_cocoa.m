#ifdef FILEDIALOG_COCOA

#import <Cocoa/Cocoa.h>

#define UNUSED(x) (void)(x);

#define NS_BEGIN() \
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];    \
    NSApplication *app = [NSApplication sharedApplication]; UNUSED(app);


#define NS_END() \
    [pool release];

static const char*
COCOA_OpenFileDialog(const char* title)
{
    NS_BEGIN();
    const char* filename = NULL;
    NSOpenPanel * panel = [NSOpenPanel openPanel];

    [panel setCanChooseFiles:YES];
    [panel setAllowsMultipleSelection:NO];
    [panel setTitle : [NSString stringWithCString: title]];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = [[panel filename] UTF8String];
    }

    NS_END();
    return filename;
}

static const char*
COCOA_SaveFileDialog(const char* title)
{
    NS_BEGIN();
    const char* filename = NULL;
    NSSavePanel* panel = [NSSavePanel savePanel];

    [panel setTitle : [NSString stringWithCString : title]];
    [panel setPrompt : @"Filename:"];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = [[panel filename] UTF8String];
    }

    NS_END();
    return filename;
}

static const char*
COCOA_FolderFileDialog(const char* title)
{
    NS_BEGIN();
    const char* filename = NULL;
    NSOpenPanel * panel = [NSOpenPanel openPanel];

    [panel setCanChooseDirectories:YES];
    [panel setCanChooseFiles:NO];
    [panel setAllowsMultipleSelection:NO];
    [panel setTitle : [NSString stringWithCString: title]];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = [[panel filename] UTF8String];
    }

    NS_END();
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
    }
}

void
COCOA_FreeFileDialogFilename(char* filename)
{
    /* the pointer is set like this:
     *      filename = [ns_string UTF8String];
     *
     * TODO: what should we do to free this?
     */
}


static const wchar_t*
COCOA_OpenFileDialogW(const wchar_t* title)
{
    NS_BEGIN();
    const wchar_t* filename = NULL;
    NSOpenPanel * panel = [NSOpenPanel openPanel];

    [panel setCanChooseFiles:YES];
    [panel setAllowsMultipleSelection:NO];
    [panel setTitle : [[NSString alloc] initWithBytes:title length:SDL_wcslen(title) * sizeof(*title) encoding:NSUTF32LittleEndianStringEncoding]];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = (wchar_t*)[[panel filename] cStringUsingEncoding:NSUTF32LittleEndianStringEncoding];
    }

    NS_END();
    return filename;
}

static const wchar_t*
COCOA_SaveFileDialogW(const wchar_t* title)
{
    NS_BEGIN();
    const char* filename = NULL;
    NSSavePanel* panel = [NSSavePanel savePanel];

    [panel setTitle : [[NSString alloc] initWithBytes:title length:SDL_wcslen(title) * sizeof(*title) encoding:NSUTF32LittleEndianStringEncoding]];
    [panel setPrompt : @"Filename:"];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = (wchar_t*)[[panel filename] cStringUsingEncoding:NSUTF32LittleEndianStringEncoding];
    }

    NS_END();
    return filename;
}

static const wchar_t*
COCOA_FolderFileDialogW(const wchar_t* title)
{
    NS_BEGIN();
    const char* filename = NULL;
    NSOpenPanel * panel = [NSOpenPanel openPanel];

    [panel setCanChooseDirectories:YES];
    [panel setCanChooseFiles:NO];
    [panel setAllowsMultipleSelection:NO];
    [panel setTitle : [[NSString alloc] initWithBytes:title length:SDL_wcslen(title) * sizeof(*title) encoding:NSUTF32LittleEndianStringEncoding]];

    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        filename = (wchar_t*)[[panel filename] cStringUsingEncoding:NSUTF32LittleEndianStringEncoding];
    }

    NS_END();
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
    }
}

void
COCOA_FreeFileDialogFilenameW(wchar_t* filename)
{
    /* the pointer is set like this:
     *      filename = [ns_string UTF8String];
     *
     * TODO: what should we do to free this?
     */
}

#endif /* FILEDIALOG_COCOA */
