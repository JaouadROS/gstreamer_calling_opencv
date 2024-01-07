
#include <gst/base/gstbasetransform.h>
#include <gst/gst.h>
#include <gst/video/gstvideofilter.h>
#include <gst/opencv/gstopencvvideofilter.h>
#include <gst/video/video-format.h>
#include <gst/video/video-info.h>
#include <gst/opencv/opencv-prelude.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define PACKAGE "cvimageprocessingpackage"

/* #defines don't like whitespacey bits */
#define GST_TYPE_CV_IMAGE_PROCESSING \
  (gst_cv_image_processing_get_type())
#define GST_CV_IMAGE_PROCESSING(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_CV_IMAGE_PROCESSING,GstCvEqualizeHist))
#define GST_CV_IMAGE_PROCESSING_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_CV_IMAGE_PROCESSING,GstCvEqualizeHistClass))
#define GST_IS_CV_IMAGE_PROCESSING(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_CV_IMAGE_PROCESSING))
#define GST_IS_CV_IMAGE_PROCESSING_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_CV_IMAGE_PROCESSING))

typedef struct _GstCvEqualizeHist      GstCvEqualizeHist;
typedef struct _GstCvEqualizeHistClass GstCvEqualizeHistClass;

struct _GstCvEqualizeHist
{
  GstOpencvVideoFilter element;
};

struct _GstCvEqualizeHistClass
{
  GstOpencvVideoFilterClass parent_class;
};

GType gst_cv_image_processing_get_type (void);

GST_ELEMENT_REGISTER_DECLARE (cvimageprocessing);

GST_DEBUG_CATEGORY_STATIC (gst_cv_image_processing_debug);
#define GST_CAT_DEFAULT gst_cv_image_processing_debug

static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS (GST_VIDEO_CAPS_MAKE ("GRAY8")));

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS (GST_VIDEO_CAPS_MAKE ("GRAY8")));

G_DEFINE_TYPE_WITH_CODE (GstCvEqualizeHist, gst_cv_image_processing,
    GST_TYPE_OPENCV_VIDEO_FILTER,
    GST_DEBUG_CATEGORY_INIT (gst_cv_image_processing_debug, "cvimageprocessing", 0,
        "cvimageprocessing");
    );
GST_ELEMENT_REGISTER_DEFINE (cvimageprocessing, "cvimageprocessing", GST_RANK_NONE,
    GST_TYPE_CV_IMAGE_PROCESSING);

static GstFlowReturn gst_cv_image_processing_transform (GstOpencvVideoFilter *
    filter, GstBuffer * buf, cv::Mat img, GstBuffer * outbuf, cv::Mat outimg);

static void
gst_cv_image_processing_class_init (GstCvEqualizeHistClass * klass)
{
  GstOpencvVideoFilterClass *gstopencvbasefilter_class;
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  gstopencvbasefilter_class = (GstOpencvVideoFilterClass *) klass;

  gstopencvbasefilter_class->cv_trans_func = gst_cv_image_processing_transform;

  gst_element_class_add_static_pad_template (element_class, &src_factory);
  gst_element_class_add_static_pad_template (element_class, &sink_factory);

  gst_element_class_set_static_metadata (element_class,
      "cvimageprocessing",
      "Transform/Effect/Video",
      "Applies cvimageprocessing OpenCV function to the image",
      "Thiago Santos<thiago.sousa.santos@collabora.co.uk>");
}

static void
gst_cv_image_processing_init (GstCvEqualizeHist * filter)
{
  gst_opencv_video_filter_set_in_place (GST_OPENCV_VIDEO_FILTER_CAST (filter),
      FALSE);
}

static GstFlowReturn
gst_cv_image_processing_transform (GstOpencvVideoFilter * base,
    GstBuffer * buf, cv::Mat img, GstBuffer * outbuf, cv::Mat outimg)
{
  cv::equalizeHist (img, outimg);
  return GST_FLOW_OK;
}

static gboolean
plugin_init (GstPlugin * plugin)
{
  return GST_ELEMENT_REGISTER (cvimageprocessing, plugin);
}

GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    cvimageprocessing,
    "GStreamer Image Processing Plugin",
    plugin_init, 
    "5.0", 
    "LGPL", 
    "Image Processing Using OpenCV Package",
   "Inspired by cvequalizehist plugin" 
)