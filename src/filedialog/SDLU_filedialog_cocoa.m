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
    /* what should we do to free the memory??? */
}
