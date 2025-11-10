#include "amethyst/runtime/mod/ModDependency.hpp"
#include "amethyst/runtime/mod/ModInfo.hpp"

namespace Amethyst {
ModDependency::ModDependency(
    const std::string& uuid, 
    const std::string& modNamespace, 
    const std::string& range, 
    bool isSoft) :
    UUID(uuid),
    Namespace(modNamespace),
    RangeString(range),
    IsSoft(isSoft)
{
    if (!semver::parse(range, Range) || range.empty()) {
        semver::parse(">=0.0.0", Range);
    }
}

bool ModDependency::IsNamespaceDependency() const
{
    return UUID.empty() && !Namespace.empty();
}

bool ModDependency::Equals(const ModDependency& other) const
{
    return UUID == other.UUID && Namespace == other.Namespace && IsSoft == other.IsSoft;
}

bool ModDependency::operator==(const ModDependency& other) const
{
    return Equals(other);
}

bool ModDependency::operator!=(const ModDependency& other) const
{
    return !(*this == other);
}

bool ModDependency::operator<(const ModDependency& other) const
{
    if (UUID != other.UUID) {
        return UUID < other.UUID;
    }
    if (Namespace != other.Namespace) {
        return Namespace < other.Namespace;
    }
    return RangeString < other.RangeString;
}

bool ModDependency::MatchesMod(const ModInfo& mod, bool checkVersion) const
{
    if (checkVersion && MatchesVersion(mod.Version)) {
        return false;
    }
    return (UUID.empty() || UUID == mod.UUID) && (Namespace.empty() || Namespace == mod.Namespace);
}

bool ModDependency::MatchesVersion(const Version& version) const
{
    return version.prerelease_tag() == "dev" || Range.contains(version);
}

std::string ModDependency::GetDependencyIdentification() const
{
    if (!UUID.empty())
        return UUID;
    if (!Namespace.empty())
        return Namespace;
    return "<unknown>";
}
} // namespace Amethyst