/**
 * This enum provides the names of the predefined registry keys.
 *
 * @author  Gabriel Daenner
 * @version 1.1.0
 */
public enum HKEY
{
    /**
     * Registry entries subordinate to this key define types (or classes)
     * of documents and the properties associated with those types.
     * Warning: Write requires elevated priviliges.
     */
    HKEY_CLASSES_ROOT("HKEY_CLASSES_ROOT"),

    /**
     * Contains information about the current hardware profile of the local
     * computer system.
     * Warning: Write requires elevated priviliges.
     */
    HKEY_CURRENT_CONFIG("HKEY_CURRENT_CONFIG"),

    /**
     * Registry entries subordinate to this key define the preferences of the
     * current user.
     */
    HKEY_CURRENT_USER("HKEY_CURRENT_USER"),

    /**
     * Registry entries subordinate to this key define the physical state of
     * the computer, including data about the bus type, system memory, and
     * installed hardware and software.
     * Warning: Write requires elevated priviliges.
     */
    HKEY_LOCAL_MACHINE("HKEY_LOCAL_MACHINE"),

    /**
     * Registry entries subordinate to this key define the default user
     * configuration for new users on the local computer and the user
     * configuration for the current user.
     */
    HKEY_USERS("HKEY_USERS");

    private final String name;

    private HKEY(String name)
    {
        this.name = name;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public String toString()
    {
        return this.name;
    }
}
