#include <gst/gst.h>

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    GstElement *pipeline = gst_pipeline_new("my-pipeline");
    GstElement *source = gst_element_factory_make("videotestsrc", "source");
    GstElement *yuv_example = gst_element_factory_make("cvimageprocessing", "imageprocessing");
    GstElement *sink = gst_element_factory_make("autovideosink", "sink");
    GstElement *converter = gst_element_factory_make("videoconvert", "converter");

    if (!pipeline || !source || !yuv_example || !sink || !converter) {
        g_printerr("One or more elements could not be created. Exiting.\n");
        return -1;
    }

    gst_bin_add_many(GST_BIN(pipeline), source, yuv_example, sink, converter, NULL);

    if (!gst_element_link_many(source, yuv_example, converter, sink, NULL)) {
        g_printerr("Elements could not be linked. Exiting.\n");
        return -1;
    }

    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    // Clean up
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(pipeline));
    g_main_loop_unref(loop);

    return 0;
}
