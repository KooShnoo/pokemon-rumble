#include <nw4r/snd.h>

namespace nw4r {
namespace snd {

void WaveSoundHandle::DetachSound() {
    if (IsAttachedSound()) {
        if (mSound->mTempSpecialHandle == this) {
            mSound->mTempSpecialHandle = NULL;
        }
    }

    if (mSound != NULL) {
        mSound = NULL;
    }
}

} // namespace snd
} // namespace nw4r
