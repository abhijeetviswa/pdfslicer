#include "viewchild.hpp"

namespace Slicer {

ViewChild::ViewChild(const Glib::RefPtr<Page>& page,
                     int targetSize,
                     ctpl::thread_pool& threadPool)
    : m_page{page}
    , m_targetSize{targetSize}
{
    int width, height;
    std::tie(width, height) = m_page->scaledSize(m_targetSize);
    set_size_request(width, height);

    m_spinner.set_size_request(38, 38);
    m_spinner.start();
    pack_start(m_spinner, true, false);

    m_signalRendered.connect([this]() {
        showPage();
    });

    threadPool.push([this](int) {
        renderPage();
        m_signalRendered.emit();
    });
}

void ViewChild::renderPage()
{
    auto pixbuf = m_page->renderPage(m_targetSize);
    m_thumbnail.set(pixbuf);
}

void ViewChild::showPage()
{
    m_spinner.stop();
    pack_start(m_thumbnail);
    m_thumbnail.show();
    m_spinner.hide();
}

} // namespace Slicer